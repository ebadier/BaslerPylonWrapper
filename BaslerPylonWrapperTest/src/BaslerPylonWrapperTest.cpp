/******************************************************************************************************************************************************
* MIT License																																		  *
*																																					  *
* Copyright (c) 2024																																  *
* Emmanuel Badier <emmanuel.badier@gmail.com>																										  *
* 																																					  *
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),  *
* to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,  *
* and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:		  *
* 																																					  *
* The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.					  *
* 																																					  *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, *
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 																							  *
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 		  *
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.							  *
******************************************************************************************************************************************************/

#include "framework.h"

#include <iostream>

#include "BaslerPylonWrapperC.h"

#define CAMERA_1_SN "24551463"
#define CAMERA_2_SN "24794830"
#define VIDEO_FILE_1 "./Video1.mp4"
#define VIDEO_FILE_2 "./Video2.mp4"

#define SPACE_KEYCODE 32
#define ESCAPE_KEYCODE 27

int main()
{
    Init();

    std::cout << "Press Space to start/stop cameras recording multiple times." << std::endl;
    std::cout << "Press Escape to exit." << std::endl;
    bool quit = false;
    while (!quit)
    {
        if (GetAsyncKeyState(SPACE_KEYCODE) & 0x8000)
        {
            if (IsRecording())
            {
                StopRecording();
                std::cout << "Recording Stopped." << std::endl;
            }
            else
            {
                // The same video files are overwritten each time
                PrepareRecording(CAMERA_1_SN, VIDEO_FILE_1);
                PrepareRecording(CAMERA_2_SN, VIDEO_FILE_2);
                StartRecording();
                std::cout << "Recording Started." << std::endl;
            }
        }
        else if (GetAsyncKeyState(ESCAPE_KEYCODE) & 0x8000)
        {
            quit = true;
        }

        if (HasError())
        {
            std::cout << GetErrors() << std::endl;
        }
        
        Sleep(100);
    }

    Terminate();

    return EXIT_SUCCESS;
}
