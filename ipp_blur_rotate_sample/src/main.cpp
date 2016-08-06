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

#define VIDEO_WINMAIN_ARGS

#include <stdio.h>
#include <iostream>

#include "ipp_blur_rotate.h"
#include "ipp_blur_rotate_video.h"

const char* filename = "Image.bmp";

int main(int argc, char *argv[])
{
    try
    {
        ipp_blur_rotate_video video;
        ipp_blur_rotate iBlurRotate;

        if (iBlurRotate.loadFileBMP(filename))
        {
            IppiSize winSize = iBlurRotate.windowSize();
            // video layer init
            if (video.init_window(winSize.width, winSize.height) )
            {
                video.calc_fps = false;
                video.threaded = 1;
                // initialize ////////////
                video.set_object( iBlurRotate );
                // main loop
                video.main_loop();
            }
            else
            {
                std::cerr << "Cannot initialize video layer\n";
            }
        }
        else
        {
            std::cerr << "Cannot load the file: " << filename << "\n";
        }

        video.terminate();
    }
    catch ( std::exception& e )
    {
        std::cerr << "error occurred. error text is :\"" << e.what() << "\"\n";

        return 1;
    }

    return 0;
}
