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

#include "pylon/TlFactory.h"
#include "pylon/PixelTypeMapper.h"

#include "BaslerPylonWrapper.h"

namespace PylonWrapper
{
	CImageEventVideoWriter::CImageEventVideoWriter(Pylon::CVideoWriter* pVideoWriter) : _videoWriter(pVideoWriter)
	{

	}

	CImageEventVideoWriter::~CImageEventVideoWriter()
	{
		_videoWriter = NULL;
	}

	void CImageEventVideoWriter::OnImageGrabbed(Pylon::CInstantCamera&, const Pylon::CGrabResultPtr& ptrGrabResult)
	{
		if ((_videoWriter != NULL) && _videoWriter->IsOpen())
		{
			_videoWriter->Add(ptrGrabResult);
		}
	}

	BaslerPylonWrapper::BaslerPylonWrapper() : _cameras(), _videoWriters(), _isRecording(false), _hasError(false), _errorsLog()
	{
		Pylon::PylonInitialize();

		if (!Pylon::CVideoWriter::IsSupported())
		{
			_errorsLog.append("[BaslerPylonWrapper] Error: VideoWriter is not supported at the moment. Please install the pylon Supplementary Package for MPEG-4 which is available on the Basler website.\n");
			_hasError = true;
		}
	}

	BaslerPylonWrapper::~BaslerPylonWrapper()
	{
		if (_isRecording)
		{
			StopRecording();
		}

		for (size_t i = 0; i < _cameras.size(); ++i)
		{
			delete _videoWriters[i];
			_videoWriters[i] = NULL;
			delete _cameras[i];
			_cameras[i] = NULL;
		}
		_videoWriters.clear();
		_cameras.clear();

		Pylon::PylonTerminate();
	}

	void BaslerPylonWrapper::PrepareRecording(const char* pDeviceSN, const char* pVideoFilePath, uint32_t pQuality)
	{
		try
		{
			Pylon::CInstantCamera* camera = NULL;
			Pylon::CVideoWriter* videoWriter = NULL;

			// Camera already exists ?
			for (size_t i = 0; i < _cameras.size(); ++i)
			{
				if (_cameras[i]->GetDeviceInfo().GetSerialNumber() == pDeviceSN)
				{
					camera = _cameras[i];
					videoWriter = _videoWriters[i];
					break;
				}
			}

			// We need to create the camera and the videoWriter.
			if (camera == NULL)
			{
				Pylon::CTlFactory& factory = Pylon::CTlFactory::GetInstance();
				Pylon::DeviceInfoList devices;
				factory.EnumerateDevices(devices, true);
				for (size_t i = 0; i < devices.size(); ++i)
				{
					if (devices[i].GetSerialNumber() == pDeviceSN)
					{
						camera = new Pylon::CInstantCamera(factory.CreateDevice(devices[i]));
						_cameras.push_back(camera);

						videoWriter = new Pylon::CVideoWriter();
						_videoWriters.push_back(videoWriter);

						CImageEventVideoWriter* imageEvent = new CImageEventVideoWriter(videoWriter);
						camera->RegisterImageEventHandler(imageEvent, Pylon::RegistrationMode_Append, Pylon::Cleanup_Delete); // imageEvent will be destroyed by CInstantCamera object.

						break;
					}
				}
			}

			if (camera == NULL)
			{
				_errorsLog.append("[BaslerPylonWrapper] Error: Camera with SN (");
				_errorsLog.append(pDeviceSN);
				_errorsLog.append(") not found !\n");
				_hasError = true;
				return;
			}

			// Open the camera device
			camera->Open();
			// Configure videoWriter with parameters already stored in the camera device.
			// The parameters could be adjusted using the Basler PylonViewer application.
			// https://www.baslerweb.com/en/software/pylon/pylon-viewer/
			auto& camerasParams = camera->GetNodeMap();
			Pylon::CIntegerParameter width(camerasParams, "Width");
			Pylon::CIntegerParameter height(camerasParams, "Height");
			Pylon::CFloatParameter frameRate(camerasParams, "AcquisitionFrameRate");
			Pylon::CEnumParameter pixelFormat(camerasParams, "PixelFormat");
			// Map the pixelType
			Pylon::CPixelTypeMapper pixelTypeMapper(&pixelFormat);
			Pylon::EPixelType pixelType = pixelTypeMapper.GetPylonPixelTypeFromNodeValue(pixelFormat.GetIntValue());
			// Set parameters before opening the video writer.
			videoWriter->SetParameter(
				(uint32_t)width.GetValue(),
				(uint32_t)height.GetValue(),
				pixelType,
				frameRate.GetValue(),
				pQuality);
			// Open the video file to write
			videoWriter->Open(pVideoFilePath);
		}
		catch (const Pylon::GenericException & e)
		{
			_errorsLog.append("[BaslerPylonWrapper] Error:\n");
			_errorsLog.append(e.what());
			_hasError = true;
		}
	}

	void BaslerPylonWrapper::StartRecording()
	{
		try
		{
			for (size_t i = 0; i < _cameras.size(); ++i)
			{
				// Start camera grabbing thread
				_cameras[i]->StartGrabbing(Pylon::EGrabStrategy::GrabStrategy_OneByOne, Pylon::EGrabLoop::GrabLoop_ProvidedByInstantCamera);
			}
			_isRecording = true;
		}
		catch (const Pylon::GenericException & e)
		{
			_errorsLog.append("[BaslerPylonWrapper] Error:\n");
			_errorsLog.append(e.what());
			_hasError = true;
		}
	}
	void BaslerPylonWrapper::StopRecording()
	{
		try
		{
			for (size_t i = 0; i < _cameras.size(); ++i)
			{
				// Stop camera grabbing thread
				_cameras[i]->StopGrabbing();
				// Close the video file
				_videoWriters[i]->Close();
				// Close the camera device
				_cameras[i]->Close();
			}
			_isRecording = false;
		}
		catch (const Pylon::GenericException & e)
		{
			_errorsLog.append("[BaslerPylonWrapper] Error:\n");
			_errorsLog.append(e.what());
			_hasError = true;
		}
	}
}