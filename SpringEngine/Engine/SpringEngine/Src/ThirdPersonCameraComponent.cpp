#include "Precompiled.h"
#include "ThirdPersonCameraComponent.h"

#include "GameObject.h"
using namespace SpringEngine;
using namespace SpringEngine::Math;

void ThirdPersonCameraComponent::Initialize()
{
    mCameraComponent = GetOwner().GetComponent<CameraComponent>();
    mPlayerTransform = GetOwner().GetComponent<TransformComponent>();

    ASSERT(mCameraComponent != nullptr, "ThirdPersonCameraComponent: Requires CameraComponent.");
    ASSERT(mPlayerTransform != nullptr, "ThirdPersonCameraComponent: Requires TransformComponent.");
}

void ThirdPersonCameraComponent::Update(float deltaTime)
{
    Vector3 cameraPosition = mPlayerTransform->position;
    Vector3 forward = mPlayerTransform->GetForward();

    cameraPosition -= forward * mDistance;
    cameraPosition.y += mHeightOffset;

    mCameraComponent->GetCamera().SetPosition(cameraPosition);
    mCameraComponent->GetCamera().SetLookAt(mPlayerTransform->position);
}

void ThirdPersonCameraComponent::Terminate()
{
}
