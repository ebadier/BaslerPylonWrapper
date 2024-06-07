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

#include <vector>
#include <pylon/stdinclude.h>
#include <pylon/PylonUtility.h>
#include <pylon/InstantCamera.h>
#include <pylon/ImageEventHandler.h>
#include <pylon/VideoWriter.h>

namespace PylonWrapper
{
	class CImageEventVideoWriter : public Pylon::CImageEventHandler
	{
	public:
		CImageEventVideoWriter(Pylon::CVideoWriter* pVideoWriter);
		~CImageEventVideoWriter();
		virtual void OnImageGrabbed(Pylon::CInstantCamera& /*camera*/, const Pylon::CGrabResultPtr& ptrGrabResult);

	private:
		Pylon::CVideoWriter* _videoWriter;
	};

	class BaslerPylonWrapper
	{
	public:
		BaslerPylonWrapper();
		~BaslerPylonWrapper();

		inline const char* GetErrors()const { return _errorsLog.c_str(); }
		inline bool HasError()const { return _hasError; }
		void PrepareRecording(const char* pDeviceSN, const char* pVideoFilePath, double pFramesPerSecond = 60.0, uint32_t pQuality = 90);
		void StartRecording();
		inline bool IsRecording()const { return _isRecording; }
		void StopRecording();

	private:
		std::vector<Pylon::CInstantCamera*> _cameras;
		std::vector<Pylon::CVideoWriter*> _videoWriters;
		bool _isRecording;
		bool _hasError;
		std::string _errorsLog;
	};
}