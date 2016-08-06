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

#ifndef IPP_BLUR_ROTATE_VIDEO_H_
#define IPP_BLUR_ROTATE_VIDEO_H_

#include "ipp_blur_rotate.h"

extern video *v;

/*
// Time operations
*/
#ifdef _WIN32
void time_sleep(unsigned int msec)
{
    if (msec)
        Sleep(msec);
}

#else
#include <sched.h>

void time_sleep(unsigned int msec)
{
    if (msec)
        usleep(1000 * msec);
    else
        sched_yield();
}
#endif

class ipp_blur_rotate_video : public video
{
    ipp_blur_rotate *ibr;

private:

    void on_key( int key )
    {
        if ( ibr )
        {
            ibr->onKey( key );
        }
    }

    void on_process()
    {
        if ( ibr )
        {
            while (v->running)
            {
                ibr->process(get_drawing_memory());
                video::next_frame();
            #ifndef _WIN32
                time_sleep(10);
            #endif
            }
        }
    }

public:
    ipp_blur_rotate_video() :ibr(0)
    {
        title = "Intel(R) IPP: blur + rotate tutorial";
        v = this;
    }

    void set_object( ipp_blur_rotate &_ibr )
    {
        ibr = &_ibr;
    }
};

#endif /* IPP_BLUR_ROTATE_VIDEO_H_ */
