#include "Precompiled.h"

#include "GameObject.h"
#include "GameWorld.h"
#include "CameraService.h"
#include "FirstPersonCameraComponent.h"

using namespace SpringEngine;
using namespace SpringEngine::Graphics;

void FirstPersonCameraComponent::Initialize()
{
    mCameraComponent = GetOwner().GetComponent<CameraComponent>();
    mPlayerTransform = GetOwner().GetComponent<TransformComponent>();
    ASSERT(mCameraComponent != nullptr, "FirstPersonCameraComponent: Requires CameraComponent.");
    ASSERT(mPlayerTransform != nullptr, "FirstPersonCameraComponent: Requires TransformComponent.");
}

void FirstPersonCameraComponent::Terminate()
{
}

void FirstPersonCameraComponent::Update(float deltaTime)
{
    Vector3 cameraPosition = mPlayerTransform->position;
    cameraPosition.y += mHeightOffset;  

    mCameraComponent->GetCamera().SetPosition(cameraPosition);
    mCameraComponent->GetCamera().SetLookAt(cameraPosition);
}
