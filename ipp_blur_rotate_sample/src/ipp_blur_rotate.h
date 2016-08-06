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

#ifndef IPP_BLUR_ROTATE_H_
#define IPP_BLUR_ROTATE_H_

#include "ippi.h"
#include "gui/video.h"

// The main processing class
class ipp_blur_rotate
{
    /* updated filter mask should be applied */
    bool bFilterUpdate;
    /* updated rotation coefficients (angle and shifts) should be applied */
    bool bRotateUpdate;
    /* redraw the window */
    bool bRedraw;

    /* source image size */
    IppiSize srcSize;
    /* destination image size (should include whole rotated image) */
    IppiSize dstSize;

    /* Pointer to the source image data */
    Ipp8u *pSrc;
    /* Pointer to the blurred image data */
    Ipp8u *pBlur;
    /* Pointer to the blurred and rotated image data */
    Ipp8u *pBlurRot;

    /* image steps */
    int srcStep, blurStep, blurRotStep;

    /* rotation angle */
    double angle;

    /* size of mask for image blurring */
    IppiSize maskSize;

public:
    /* Constructor */
    ipp_blur_rotate();

    /* Destructor */
   ~ipp_blur_rotate();

    /* load image data from bmp file */
    bool loadFileBMP( const char* bmpImageFile );

    /* Returns size of required rendering area */
    IppiSize windowSize() const { return dstSize; };

    /* Key processing */
    void onKey( int key );

    /* Run processing */
    void process(const drawing_memory &dm);
};


#endif /* IPP_BLUR_ROTATE_H_ */
