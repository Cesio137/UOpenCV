// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenCVObject.h"

#include "AnimGraphRuntime/Public/AnimNodes/AnimNode_RandomPlayer.h"
#include "opencv2/core/opencl/runtime/autogenerated/opencl_clfft.hpp"

UOpenCVObject::UOpenCVObject()
{
	
}

UOpenCVObject::FOpenCL::FOpenCL()
{
	
}

bool UOpenCVObject::FOpenCL::CreateOpenCLContext(EDeviceType EType)
{
	switch (EType)
	{
	case EDeviceType::TYPE_DEFAULT :
		return CVContext.create(CVDevice.TYPE_DEFAULT);
		
	case EDeviceType::TYPE_CPU  :
		return CVContext.create(CVDevice.TYPE_CPU);

	case EDeviceType::TYPE_GPU  :
		return CVContext.create(CVDevice.TYPE_GPU);

	case EDeviceType::TYPE_ACCELERATOR :
		return CVContext.create(CVDevice.TYPE_ACCELERATOR);

	case EDeviceType::TYPE_DGPU  :
		return CVContext.create(CVDevice.TYPE_DGPU );

	case EDeviceType::TYPE_IGPU :
        return CVContext.create(CVDevice.TYPE_IGPU);
        		
	case EDeviceType::TYPE_ALL :
		return CVContext.create(CVDevice.TYPE_ALL);
	}
	return CVContext.create(CVDevice.TYPE_DEFAULT);
}

void UOpenCVObject::FOpenCL::SetUseOpenCL(bool flag)
{
	ocl::setUseOpenCL(flag);
}

bool UOpenCVObject::FOpenCL::GetUseOpenCL()
{
	return ocl::useOpenCL();
}

int UOpenCVObject::FOpenCL::GetNDevices()
{
	return static_cast<int>(CVContext.ndevices());
}

FCVOpenCLDevice UOpenCVObject::FOpenCL::GetDeviceByID(int Index)
{
	CVDevice = CVContext.device(Index);
	FCVOpenCLDevice CurrentDevice;

	CurrentDevice.DeviceName = ANSI_TO_TCHAR(CVDevice.name().c_str());
	CurrentDevice.VendorName = ANSI_TO_TCHAR(CVDevice.vendorName().c_str());
	CurrentDevice.bIsAvaliable = CVDevice.available();
	CurrentDevice.bHasImageSuport = CVDevice.imageSupport();
	CurrentDevice.OpenCLVersion = ANSI_TO_TCHAR(CVDevice.OpenCLVersion().c_str());
	CurrentDevice.DriverVersion = ANSI_TO_TCHAR(CVDevice.driverVersion().c_str());
	CurrentDevice.Index = Index;

	return CurrentDevice;
}

FString UOpenCVObject::FOpenCL::GetOpenCVVersion()
{
	return FString::FromInt(cv::getVersionMajor())+"."+FString::FromInt(cv::getVersionMinor())+"."+FString::FromInt(cv::getVersionRevision());
}