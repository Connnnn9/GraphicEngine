#include "Precompiled.h"
#include "FirstPersonCameraComponent.h"
#include "UpdateService.h"
#include "GameObject.h"

#include "GameWorld.h"
#include "CameraService.h"

using namespace SpringEngine;
using namespace SpringEngine::Graphics;
using namespace SpringEngine::Input;

void FirstPersonCameraComponent::Initialize()
{

	UpdateService* updateService = GetOwner().GetWorld().GetService<UpdateService>();
	ASSERT(updateService != nullptr, "FirstPersonCameraComponent: Requires UpdateService.");
	updateService->Register(this);

	CameraService* cameraService = GetOwner().GetWorld().GetService<CameraService>();
	ASSERT(cameraService != nullptr, "FirstPersonCameraComponent: CameraService not found.");

	mCameraComponent = GetOwner().GetComponent<CameraComponent>();
	ASSERT(mCameraComponent != nullptr, "FirstPersonCameraComponent: Requires CameraComponent.");
	cameraService->SetFirstPersonCamera(mCameraComponent);

	GameObject* player = GetOwner().GetWorld().GetGameObject("TestObject1");
	ASSERT(player != nullptr, "FirstPersonCameraComponent: Player object not found.");
	mPlayerTransform = player->GetComponent<TransformComponent>();

	mPlayerTransform = player->GetComponent<TransformComponent>();
	ASSERT(mPlayerTransform != nullptr, "FirstPersonCameraComponent: Requires TransformComponent.");

}

void FirstPersonCameraComponent::Terminate()
{
	UpdateService* updateService = GetOwner().GetWorld().GetService<UpdateService>();
	ASSERT(updateService != nullptr, "FirstPersonCameraComponent: game world requires an UpdateService.");
	updateService->UnRegister(this);

	mCameraComponent = nullptr;
	mPlayerTransform = nullptr;
}

void FirstPersonCameraComponent::Update(float deltaTime)
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

	mTargetPosition = mPlayerTransform->position;
	mTargetPosition.y += mHeightOffset;
	Vector3 cameraPosition = Lerp(mCameraComponent->GetCamera().GetPosition(), mTargetPosition, deltaTime * 10.0f);

	mCameraComponent->GetCamera().SetPosition(cameraPosition);
	mCameraComponent->GetCamera().SetLookAt(cameraPosition + forward);
	LOG("Camera Following Player at Position: X=%.6f, Y=%.6f, Z=%.6f", cameraPosition.x, cameraPosition.y, cameraPosition.z);
}

void FirstPersonCameraComponent::DebugUI()
{
	if (ImGui::CollapsingHeader("FirstPersonCamera Settings"))
	{
		ImGui::SliderFloat("Height Offset", &mHeightOffset, 0.0f, 5.0f);
		ImGui::SliderFloat("Yaw Sensitivity", &mYawSensitivity, 0.01f, 1.0f);
	}
}

void FirstPersonCameraComponent::Deserialize(const rapidjson::Value& value)
{
	if (value.HasMember("HeightOffset"))
	{
		mHeightOffset = value["HeightOffset"].GetFloat();
	}
	if (value.HasMember("YawSensitivity"))
	{
		mYawSensitivity = value["YawSensitivity"].GetFloat();
	}
}

