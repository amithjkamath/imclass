/* 
// Copyright 2005 2016 Intel Corporation All Rights Reserved.
// 
// The source code, information and material ("Material") contained herein is
// owned by Intel Corporation or its suppliers or licensors, and title
// to such Material remains with Intel Corporation or its suppliers or
// licensors. The Material contains proprietary information of Intel
// or its suppliers and licensors. The Material is protected by worldwide
// copyright laws and treaty provisions. No part of the Material may be used,
// copied, reproduced, modified, published, uploaded, posted, transmitted,
// distributed or disclosed in any way without Intel's prior express written
// permission. No license under any patent, copyright or other intellectual
// property rights in the Material is granted to or conferred upon you,
// either expressly, by implication, inducement, estoppel or otherwise.
// Any license under such intellectual property rights must be express and
// approved by Intel in writing.
// 
// Unless otherwise agreed by Intel in writing,
// you may not remove or alter this notice or any other notice embedded in
// Materials by Intel or Intel's suppliers or licensors in any way.
// 
*/

#ifndef BMPREADER_H_
#define BMPREADER_H_

#include "ippi.h"

enum ReturnStatus
{
    STS_ERR_FAILED                = -999,
    STS_ERR_NOT_INITIALIZED       = -998,
    STS_ERR_NOT_ENOUGH_DATA       = -996,
    STS_ERR_NULL_PTR              = -995,
    STS_ERR_INIT                  = -899,
    STS_ERR_END_OF_STREAM         = -895,
    STS_ERR_ALLOC                 = -883,
    STS_ERR_UNSUPPORTED           = -879,
    STS_ERR_INVALID_PARAMS        = -876,
    STS_ERR_FILE_OPEN             = -875,
    STS_ERR_FORMAT                = -874,
    STS_OK                        =  0,
};

typedef int Status;

Status ReadFile(const char *pFileName, Ipp8u **pImg, IppiSize &imgSize, int &imgStep, int &numChannels);

#endif /* BMPREADER_H_ */
