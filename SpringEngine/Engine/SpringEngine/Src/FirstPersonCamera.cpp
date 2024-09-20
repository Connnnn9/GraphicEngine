#include "Precompiled.h"
#include "FirstPersonCameraComponent.h"

#include "GameObject.h"
#include "GameWorld.h"
#include "CameraService.h"

using namespace SpringEngine;
using namespace SpringEngine::Graphics;
using namespace SpringEngine::Input;

void FirstPersonCameraComponent::Initialize()
{
    mCameraComponent = GetOwner().GetComponent<CameraComponent>();
    mPlayerTransform = GetOwner().GetComponent<TransformComponent>();

    ASSERT(mCameraComponent != nullptr, "FirstPersonCameraComponent: Requires CameraComponent.");
    ASSERT(mPlayerTransform != nullptr, "FirstPersonCameraComponent: Requires TransformComponent.");
}

void FirstPersonCameraComponent::Update(float deltaTime)
{
    InputSystem* input = InputSystem::Get();

    float mouseDeltaX = input->GetMouseMoveX();
    float yawRadians = mouseDeltaX * mYawSensitivity * deltaTime;

    mCameraComponent->GetCamera().Yaw(yawRadians);

    Vector3 cameraPosition = mPlayerTransform->position;
    cameraPosition.y += mHeightOffset;

    Vector3 forward = mCameraComponent->GetCamera().GetDirection();

    mCameraComponent->GetCamera().SetPosition(cameraPosition);
    mCameraComponent->GetCamera().SetLookAt(cameraPosition + forward);
}

void FirstPersonCameraComponent::Terminate()
{
    // Clean up if necessary
}
