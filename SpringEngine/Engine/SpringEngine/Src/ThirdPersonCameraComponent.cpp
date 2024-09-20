#include "Precompiled.h"
#include "ThirdPersonCameraComponent.h"

#include "GameObject.h"
using namespace SpringEngine;
using namespace SpringEngine::Math;
using namespace SpringEngine::Input;

void ThirdPersonCameraComponent::Initialize()
{
    mCameraComponent = GetOwner().GetComponent<CameraComponent>();
    mPlayerTransform = GetOwner().GetComponent<TransformComponent>();

    ASSERT(mCameraComponent != nullptr, "ThirdPersonCameraComponent: Requires CameraComponent.");
    ASSERT(mPlayerTransform != nullptr, "ThirdPersonCameraComponent: Requires TransformComponent.");
}

void ThirdPersonCameraComponent::Update(float deltaTime)
{
    InputSystem* input = InputSystem::Get();

    float mouseDeltaX = input->GetMouseMoveX();
    float yawRadians = mouseDeltaX * mYawSensitivity * deltaTime;

    mCameraComponent->GetCamera().Yaw(yawRadians);

    Vector3 cameraPosition = mPlayerTransform->position;
    Vector3 forward = mCameraComponent->GetCamera().GetDirection(); 

    cameraPosition -= forward * mDistance;
    cameraPosition.y += mHeightOffset;

    mCameraComponent->GetCamera().SetPosition(cameraPosition);
    mCameraComponent->GetCamera().SetLookAt(mPlayerTransform->position);
}

void ThirdPersonCameraComponent::Terminate()
{
}
