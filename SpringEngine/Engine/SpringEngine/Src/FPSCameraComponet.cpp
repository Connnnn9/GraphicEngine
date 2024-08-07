#include "Precompiled.h"
#include "FPSCameraComponet.h"
#include "CameraComponet.h"
#include "GameObject.h"

#include "GameWorld.h"
#include "UpdateService.h"

using namespace SpringEngine;
using namespace SpringEngine::Graphics;
using namespace SpringEngine::Math;
using namespace SpringEngine::Input;

void FPSCameraComponet::Initialize()
{	 
	UpdateService* updateService = GetOwner().GetWorld().GetService<UpdateService>();
	ASSERT(updateService != nullptr, "FPSCameraComponent: game world requires and update service");
	updateService->Register(this);

	mCameraComponet = GetOwner().GetComponent<CameraComponet>();
}	 
	 
void FPSCameraComponet::Terminate()
{
	UpdateService* updateService = GetOwner().GetWorld().GetService<UpdateService>();
	ASSERT(updateService != nullptr, "FPSCameraComponent: game world requires and update service");
	updateService->UnRegister(this);

	mCameraComponet = nullptr;
}	 
	 
void FPSCameraComponet::Update(float deltaTime)
{
	Camera& camera = mCameraComponet->GetCamera();
	InputSystem* input = InputSystem::Get();

	const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? mShiftSpeed : mMoveSpeed;
	const float turnSpeed = mTurnSpeed;

	if (input->IsKeyDown(KeyCode::W))
	{
		camera.Walk(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::S))
	{
		camera.Walk(-moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::D))
	{
		camera.Strafe(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::A))
	{
		camera.Strafe(-moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::E))
	{
		camera.Rise(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::Q))
	{
		camera.Rise(-moveSpeed * deltaTime);
	}
	if (input->IsMouseDown(MouseButton::RBUTTON))
	{
		camera.Yaw(input->GetMouseMoveX() * turnSpeed * deltaTime);
		camera.Pitch(input->GetMouseMoveY() * turnSpeed * deltaTime);
	}
}
