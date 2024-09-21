#include "Precompiled.h"
#include "PlayerControllerComponent.h"
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
    InputSystem* input = InputSystem::Get();

    mTransformComponent = GetOwner().GetComponent<TransformComponent>();
    ASSERT(mTransformComponent != nullptr, "PlayerControllerComponent: Player requires a TransformComponent.");

    Vector3 moveDirection = Vector3::Zero;

    if (input->IsKeyDown(KeyCode::W)) 
    {
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
    }

    mTransformComponent->position += (moveDirection * mMoveSpeed * deltaTime);

    //mTransformComponent->position = newPosition;
}

void PlayerControllerComponent::Deserialize(const rapidjson::Value& value)
{
    if (value.HasMember("MoveSpeed"))
    {
        mMoveSpeed = value["MoveSpeed"].GetFloat();
    }
}
