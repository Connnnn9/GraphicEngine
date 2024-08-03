#include "Precompiled.h"
#include "CameraService.h"

#include "CameraComponet.h"

using namespace SpringEngine;
using namespace SpringEngine::Graphics;

void CameraService::DebugUI()
{
	SimpleDraw::Render(GetMain());
}

const Camera& SpringEngine::CameraService::GetMain() const
{	  
	ASSERT(mMainCamera != nullptr, "CameraService: has no main camera");
	return mMainCamera->GetCamera();
}	  
	  
void  CameraService::SetMainCamera(uint32_t index)
{	  
	if (index < mCameraEntries.size())
	{
		mMainCamera = mCameraEntries[index];
	}
}	  
	  
void  CameraService::Register(const CameraComponet* cameraComponet)
{	 
	mCameraEntries.push_back(cameraComponet);
	if (mMainCamera == nullptr)
	{
		mMainCamera = cameraComponet;
	}
}	  
	  
void  CameraService::UnRegister(const CameraComponet* cameraComponet)
{
	auto iter = std::find(mCameraEntries.begin(), mCameraEntries.end(), cameraComponet);
	if (iter != mCameraEntries.end())
	{
		if (mMainCamera == *iter) 
		{
			mMainCamera = nullptr;
		}
		mCameraEntries.erase(iter);
		if (mMainCamera == nullptr&&!mCameraEntries.empty())
		{
			mMainCamera = mCameraEntries.front();
		}
	}
}
