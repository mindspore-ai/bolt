// Copyright (C) 2019. Huawei Technologies Co., Ltd. All rights reserved.

// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef _H_DEPTHWISE_POINTWISE_CONVOLUTION
#define _H_DEPTHWISE_POINTWISE_CONVOLUTION

#include "sys.h"
#include "uni.h"
#include "tensor_desc.h"
#include "parameter_spec.h"

EE depthwise_pointwise_convolution_direct(TensorDesc inputDesc,
    INT8 *inArray,
    TensorDesc dwFilterDesc,
    const INT8 *dwFilterArray,
    TensorDesc pwFilterDesc,
    const INT8 *pwFilterArray,
    ConvolutionParamSpec convParamSpec,
    TensorDesc dwBiasDesc,
    const I32 *dwBiasArray,
    TensorDesc pwBiasDesc,
    const I32 *pwBiasArray,
    U32 tmpBytes,
    void *tmp,
    TensorDesc outputDesc,
    I32 *outArray,
    ActivationParamSpec depthwiseActivationParamSpec,
    ActivationParamSpec pointwiseActivationParamSpec,
    Arch arch);
#endif
