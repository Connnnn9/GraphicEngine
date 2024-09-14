#include "Precompiled.h"
#include "PlayerControllerComponent.h"
#include "PlayerControllerService.h"

#include "GameWorld.h"
#include "GameObject.h"
#include "Component.h"

using namespace SpringEngine;
using namespace SpringEngine::Input;
using namespace SpringEngine::Graphics;

void PlayerControllerService::Initialize()
{
	mCameraService = GetWorld().GetService<CameraService>();
		
	ASSERT(mCameraService != nullptr, "PlayerControllerService: Requires CameraService.");
}

void PlayerControllerService::Terminate()
{
}

void PlayerControllerService::Update(float deltaTime)
{
	InputSystem* input = InputSystem::Get();

	mPlayerController->Update(deltaTime);

	if (input->IsKeyPressed(KeyCode::V))
	{
		SwitchCameraView();
	}
}

void PlayerControllerService::SwitchCameraView()
{
	if (mIsFirstPerson)
	{
		mCameraService->SwitchToThirdPerson();
		mIsFirstPerson = false;
	}
	else
	{
		mCameraService->SwitchToFirstPerson();
		mIsFirstPerson = true;
	}
}
