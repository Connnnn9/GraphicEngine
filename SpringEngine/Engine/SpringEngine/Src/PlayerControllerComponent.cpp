#include "Precompiled.h"
#include "PlayerControllerComponent.h"
#include "RigidBodyComponent.h"
#include "ModelComponent.h"
#include "GameObject.h"

#include "GameWorld.h"
#include "UpdateService.h"
#include "CameraService.h"

using namespace SpringEngine;
using namespace SpringEngine::Input;
using namespace SpringEngine::Graphics;

void PlayerControllerComponent::Initialize()
{
	UpdateService* updateService = GetOwner().GetWorld().GetService<UpdateService>();
	ASSERT(updateService != nullptr, "PlayerControllerComponent: Game world requires an update service.");
	updateService->Register(this);

    mRigidBodyComponent = GetOwner().GetComponent<RigidBodyComponent>();

	mTransformComponent = GetOwner().GetComponent<TransformComponent>();
	ASSERT(mTransformComponent != nullptr, "PlayerControllerComponent: Requires TransformComponent.");

}

void PlayerControllerComponent::Terminate()
{
	UpdateService* updateService = GetOwner().GetWorld().GetService<UpdateService>();
	ASSERT(updateService != nullptr, "PlayerControllerComponent: Game world requires an update service.");
	updateService->UnRegister(this);

	mTransformComponent = nullptr;
}

void PlayerControllerComponent::Update(float deltaTime)
{
    CameraService* cameraService = GetOwner().GetWorld().GetService<CameraService>();
    if (!cameraService->IsUsingSpecialCamera())
    {
        return;
    }
    InputSystem* input = InputSystem::Get();

    mTransformComponent = GetOwner().GetComponent<TransformComponent>();
    ASSERT(mTransformComponent != nullptr, "PlayerControllerComponent: Player requires a TransformComponent.");

    Vector3 moveDirection = Vector3::Zero;

    if (input->IsKeyDown(KeyCode::W)) 
    {
        LOG("W Key Pressed: Moving Forward");
        moveDirection += Vector3::Forward;
    }
    if (input->IsKeyDown(KeyCode::S))
    {
        moveDirection += Vector3::Backward;
    }
    if (input->IsKeyDown(KeyCode::A))
    {
        moveDirection += Vector3::Left; 
    }
    if (input->IsKeyDown(KeyCode::D)) 
    {
        moveDirection += Vector3::Right;
    }

    if (Math::MagnitudeSqr(moveDirection) > 0.0f)
    {
        moveDirection = Math::Normalize(moveDirection);
        LOG("Player Move Direction: X=%.6f, Y=%.6f, Z=%.6f", moveDirection.x, moveDirection.y, moveDirection.z);
        if (mRigidBodyComponent)
        {
            Vector3 velocity = moveDirection * mMoveSpeed;
            mRigidBodyComponent->SetVelocity(velocity);
        }
        else
        {
            Vector3 newPosition = mTransformComponent->position + (moveDirection * mMoveSpeed * deltaTime);
            mTransformComponent->position = newPosition;
            LOG("New Player Position without Rigidbody: X=%.6f, Y=%.6f, Z=%.6f", newPosition.x, newPosition.y, newPosition.z);
        }
    }
    else
    {
        if (mRigidBodyComponent)
        {
            mRigidBodyComponent->SetVelocity(Vector3::Zero);
            LOG("Player Velocity Stopped: X=0.0, Y=0.0, Z=0.0");
        }
    }
}

void PlayerControllerComponent::Deserialize(const rapidjson::Value& value)
{
    if (value.HasMember("MoveSpeed"))
    {
        mMoveSpeed = value["MoveSpeed"].GetFloat();
    }
}
