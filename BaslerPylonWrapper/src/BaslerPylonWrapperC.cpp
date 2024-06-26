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

#include "BaslerPylonWrapper.h"
#include "BaslerPylonWrapperC.h"

static PylonWrapper::BaslerPylonWrapper* sWrapperInstance = NULL;

void Init()
{
	sWrapperInstance = new PylonWrapper::BaslerPylonWrapper();
}

void Terminate()
{
	delete sWrapperInstance;
	sWrapperInstance = NULL;
}

void PrepareRecording(const char* pDeviceSN, const char* pVideoFilePath, uint32_t pQuality)
{
	if (sWrapperInstance != NULL)
	{
		sWrapperInstance->PrepareRecording(pDeviceSN, pVideoFilePath, pQuality);
	}
}

void StartRecording()
{
	if (sWrapperInstance != NULL)
	{
		sWrapperInstance->StartRecording();
	}
}

BASLERPYLONWRAPPER_API bool IsRecording()
{
	if (sWrapperInstance != NULL)
	{
		return sWrapperInstance->IsRecording();
	}
	return false;
}

void StopRecording()
{
	if (sWrapperInstance != NULL)
	{
		sWrapperInstance->StopRecording();
	}
}

bool HasError()
{
	if (sWrapperInstance != NULL)
	{
		return sWrapperInstance->HasError();
	}
	return false;
}

const char* GetErrors()
{
	if (sWrapperInstance != NULL)
	{
		return sWrapperInstance->GetErrors();
	}
	return NULL;
}