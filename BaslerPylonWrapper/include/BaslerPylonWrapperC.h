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

#pragma once

#ifdef BASLERPYLONWRAPPER_EXPORTS
	#define BASLERPYLONWRAPPER_API __declspec(dllexport)
#else
	#define BASLERPYLONWRAPPER_API __declspec(dllimport)
#endif

extern "C"
{
	// Must be called first, before any other call.
	BASLERPYLONWRAPPER_API void Init();

	// Must be called for each camera, before any call to StartRecording()
	BASLERPYLONWRAPPER_API void PrepareRecording(const char* pDeviceSN, const char* pVideoFilePath, double pFramesPerSecond = 60.0, uint32_t pQuality = 90);

	// Recording of video happens in a thread and will never block the calling thread.
	BASLERPYLONWRAPPER_API void StartRecording();

	BASLERPYLONWRAPPER_API bool IsRecording();

	BASLERPYLONWRAPPER_API void StopRecording();

	BASLERPYLONWRAPPER_API bool HasError();

	BASLERPYLONWRAPPER_API const char* GetErrors();

	// Must be called at the end of the program.
	// Automatically Stop any recording in progress.
	BASLERPYLONWRAPPER_API void Terminate();
}