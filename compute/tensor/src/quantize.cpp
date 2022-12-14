// Copyright (C) 2019. Huawei Technologies Co., Ltd. All rights reserved.

// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "tensor_computing.h"
#ifdef _USE_CPU
#include "cpu/tensor_computing_cpu.h"
#endif

EE quantize(Tensor input, Tensor *output, F32 *scale, ArchInfo_t archInfo)
{
    auto arch = archInfo->arch;
    TensorDesc dDesc = input.get_desc();
    void *data = get_ptr_from_tensor(input, arch);
    TensorDesc qDesc = output->get_desc();
    void *qData = get_ptr_from_tensor(*output, arch);
    EE ret = NOT_SUPPORTED;
    if (IS_CPU(arch)) {
#ifdef _USE_CPU
        ret = quantize_cpu(dDesc, data, &qDesc, qData, scale, arch);
#endif
    }
    output->resize(qDesc);
    return ret;
}
