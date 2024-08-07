#include "Precompiled.h"
#include "CameraComponet.h"

#include "GameObject.h"
#include "GameWorld.h"
#include "CameraService.h"

using namespace SpringEngine;
using namespace SpringEngine::Graphics;

void CameraComponet::Initialize()
{
	CameraService* cameraService = GetOwner().GetWorld().GetService<CameraService>();
	ASSERT(cameraService != nullptr, "CameraComponent: GameWorld needs a camera service");

	cameraService->Register(this);
}

void CameraComponet::Terminate()
{
	CameraService* cameraService = GetOwner().GetWorld().GetService<CameraService>();
	ASSERT(cameraService != nullptr, "CameraComponent: GameWorld needs a camera service");

	cameraService->UnRegister(this);
}

Camera& CameraComponet::GetCamera()
{
	return mCamera;
}

const Camera& CameraComponet::GetCamera() const
{
	return mCamera;
}
