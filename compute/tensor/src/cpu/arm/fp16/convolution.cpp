// Copyright (C) 2019. Huawei Technologies Co., Ltd. All rights reserved.

// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "cpu/arm/fp16/tensor_computing_fp16.h"
#include "cpu/arm/fp16/convolution_winograd.h"
#include "cpu/arm/fp16/convolution_gemm.h"
#include "cpu/arm/fp16/convolution_gemm_icnchw.h"
#include "cpu/arm/fp16/convolution_direct.h"

EE convolution_fp16(TensorDesc inputDesc,
    F16 *input,
    TensorDesc filterDesc,
    const F16 *filter,
    ConvolutionParamSpec convParamSpec,
    ConvolutionForwardAlgorithm algorithm,
    TensorDesc biasDesc,
    const F16 *bias,
    U32 tmpBytes,
    void *tmp,
    TensorDesc outputDesc,
    F16 *output,
    ActivationParamSpec activationDesc,
    Arch arch)
{
    if (nullptr == input || nullptr == filter || nullptr == output || nullptr == bias ||
        nullptr == tmp) {
        CHECK_STATUS(NULL_POINTER);
    }
    if (!(inputDesc.dt == DT_F16 && filterDesc.dt == DT_F16 && outputDesc.dt == DT_F16)) {
        CHECK_STATUS(NOT_MATCH);
    }
    if (outputDesc.df != DF_NCHWC8) {
        CHECK_STATUS(NOT_MATCH);
    }
    if (inputDesc.dims[inputDesc.nDims - 2] != filterDesc.dims[filterDesc.nDims - 2] ||
        outputDesc.dims[outputDesc.nDims - 2] != filterDesc.dims[filterDesc.nDims - 1]) {
        CHECK_STATUS(NOT_MATCH);
    }

    // In some cases when we adjust the model input, the input tensor of conv can change from NCHW to NCHWc8
    // In this case we can simply change the algo, because they both require the same filter transform
    if (CONVOLUTION_ALGORITHM_GEMM_ICNCHW == algorithm && DF_NCHWC8 == inputDesc.df) {
        algorithm = CONVOLUTION_ALGORITHM_GEMM;
    }

    EE ret = SUCCESS;
    switch (algorithm) {
        case CONVOLUTION_ALGORITHM_DIRECT:
            ret = convolution_direct(inputDesc, input, filterDesc, filter, convParamSpec, biasDesc,
                bias, tmpBytes, tmp, outputDesc, output, activationDesc, arch);
            break;
        case CONVOLUTION_ALGORITHM_GEMM:
            ret = convolution_gemm(inputDesc, input, filterDesc, filter, convParamSpec, biasDesc,
                bias, tmpBytes, tmp, outputDesc, output, activationDesc, arch);
            break;
        case CONVOLUTION_ALGORITHM_WINOGRAD:
            ret = convolution_winograd(inputDesc, input, filterDesc, filter, convParamSpec,
                biasDesc, bias, tmpBytes, tmp, outputDesc, output, activationDesc, arch);
            break;
        case CONVOLUTION_ALGORITHM_GEMM_ICNCHW:
            ret = convolution_gemm_icnchw(inputDesc, input, filterDesc, filter, convParamSpec,
                biasDesc, bias, tmpBytes, tmp, outputDesc, output, activationDesc, arch);
            break;
        default:
            ret = NOT_SUPPORTED;
            break;
    }
    return ret;
}
