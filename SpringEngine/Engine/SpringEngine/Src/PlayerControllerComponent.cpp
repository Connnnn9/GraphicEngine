#include "Precompiled.h"
#include "PlayerControllerComponent.h"
#include "PlayerControllerService.h"

#include "GameObject.h"
#include "GameWorld.h"

using namespace SpringEngine;
using namespace SpringEngine::Input;
using namespace SpringEngine::Graphics;

void PlayerControllerComponent::Initialize()
{
    mTransformComponent = GetOwner().GetComponent<TransformComponent>();
    ASSERT(mTransformComponent != nullptr, "PlayerControllerComponent: Requires TransformComponent.");
}

void PlayerControllerComponent::Terminate()
{
}

void PlayerControllerComponent::Update(float deltaTime)
{
    InputSystem* input = InputSystem::Get();


    Vector3 movement = Vector3::Zero;

    if (input->IsKeyDown(KeyCode::W))
    {
        movement.z += mMoveSpeed * deltaTime;
    }
    if (input->IsKeyDown(KeyCode::S))
    {
        movement.z -= mMoveSpeed * deltaTime;
    }
    if (input->IsKeyDown(KeyCode::A))  
    {
        movement.x -= mMoveSpeed * deltaTime;
    }
    if (input->IsKeyDown(KeyCode::D))  
    {
        movement.x += mMoveSpeed * deltaTime;
    }
    mTransformComponent->position += movement;
}

void PlayerControllerComponent::Deserialize(const rapidjson::Value& value)
{
    if (value.HasMember("MoveSpeed"))
    {
        mMoveSpeed = value["MoveSpeed"].GetFloat();
    }
}
