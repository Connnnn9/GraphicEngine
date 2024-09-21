#include "Precompiled.h"
#include "ThirdPersonCameraComponent.h"
#include "GameObject.h"

#include "GameWorld.h"
#include "UpdateService.h"
#include "CameraService.h"

using namespace SpringEngine;
using namespace SpringEngine::Math;
using namespace SpringEngine::Input;

void ThirdPersonCameraComponent::Initialize()
{
	UpdateService* updateService = GetOwner().GetWorld().GetService<UpdateService>();
	ASSERT(updateService != nullptr, "ThirdPersonCameraComponent: game world requires an UpdateService.");
	updateService->Register(this);

	CameraService* cameraService = GetOwner().GetWorld().GetService<CameraService>();
	ASSERT(cameraService != nullptr, "ThirdPersonCameraComponent: CameraService not found.");

	mCameraComponent = GetOwner().GetComponent<CameraComponent>();
	ASSERT(mCameraComponent != nullptr, "ThirdPersonCameraComponent: Requires CameraComponent.");
	cameraService->SetThirdPersonCamera(mCameraComponent);

	GameObject* player = GetOwner().GetWorld().GetGameObject("TestObject1");
	ASSERT(player != nullptr, "ThirdPersonCameraComponent: Player object not found.");

	mPlayerTransform = player->GetComponent<TransformComponent>();
	ASSERT(mPlayerTransform != nullptr, "ThirdPersonCameraComponent: Requires TransformComponent.");

}

void ThirdPersonCameraComponent::Terminate()
{
	UpdateService* updateService = GetOwner().GetWorld().GetService<UpdateService>();
	ASSERT(updateService != nullptr, "ThirdPersonCameraComponent: game world requires an UpdateService.");
	updateService->UnRegister(this);

	mCameraComponent = nullptr;
	mPlayerTransform = nullptr;
}

void ThirdPersonCameraComponent::Update(float deltaTime)
{
	InputSystem* input = InputSystem::Get();

	float mouseDeltaX = input->GetMouseMoveX();
	float yawRadians = mouseDeltaX * mYawSensitivity * deltaTime;
	mYaw += yawRadians;

	if (input->IsKeyDown(KeyCode::LCONTROL)) 
	{
		float mouseDeltaY = input->GetMouseMoveY();
		mPitch -= mouseDeltaY * mPitchSensitivity * deltaTime;

		if (mPitch < mMinPitch) mPitch = mMinPitch;
		if (mPitch > mMaxPitch) mPitch = mMaxPitch;
	}

	Quaternion rotation = Quaternion::CreateFromYawPitchRoll(mYaw, mPitch, 0.0f);

	Matrix4 rotationMatrix = Matrix4::RotationQuaternion(rotation);

	Vector3 forward = Math::TransformNormal(Vector3::Forward, rotationMatrix);

	Vector3 cameraPosition = mPlayerTransform->position;
	cameraPosition -= forward * mDistance; 
	cameraPosition.y += mHeightOffset;

	mCameraComponent->GetCamera().SetPosition(cameraPosition);
	mCameraComponent->GetCamera().SetLookAt(mPlayerTransform->position);
	LOG("Player Position: X=%f, Y=%f, Z=%f", mPlayerTransform->position.x, mPlayerTransform->position.y, mPlayerTransform->position.z);
	LOG("Camera Position: X=%f, Y=%f, Z=%f", cameraPosition.x, cameraPosition.y, cameraPosition.z);
}

void ThirdPersonCameraComponent::DebugUI()
{
	if (ImGui::CollapsingHeader("ThirdPersonCamera Settings"))
	{
		ImGui::SliderFloat("Camera Distance", &mDistance, 1.0f, 20.0f);
		ImGui::SliderFloat("Height Offset", &mHeightOffset, 0.0f, 10.0f);
		ImGui::SliderFloat("Yaw Sensitivity", &mYawSensitivity, 0.01f, 1.0f);
	}
}

void ThirdPersonCameraComponent::Deserialize(const rapidjson::Value& value)
{
	if (value.HasMember("Distance"))
	{
		mDistance = value["Distance"].GetFloat();
	}
	if (value.HasMember("HeightOffset"))
	{
		mHeightOffset = value["HeightOffset"].GetFloat();
	}
	if (value.HasMember("YawSensitivity"))
	{
		mYawSensitivity = value["YawSensitivity"].GetFloat();
	}
}


