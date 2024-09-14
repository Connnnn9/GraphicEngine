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

    const Vector3& cameraForward = Vector3::Normalize(mCamera->GetDirection());  

    Vector3 cameraRight = Vector3::Normalize(Vector3::Cross(Vector3::YAxis, cameraForward)); 

    Vector3 movement = Vector3::Zero;

    if (input->IsKeyDown(KeyCode::W))  
    {
        movement += cameraForward * mMoveSpeed * deltaTime;
    }
    if (input->IsKeyDown(KeyCode::S))  
    {
        movement -= cameraForward * mMoveSpeed * deltaTime;
    }

    if (input->IsKeyDown(KeyCode::A))  
    {
        movement -= cameraRight * mMoveSpeed * deltaTime;
    }
    if (input->IsKeyDown(KeyCode::D))  
    {
        movement += cameraRight * mMoveSpeed * deltaTime;
    }
    mTransformComponent->position += movement;

    if (input->IsKeyPressed(KeyCode::V))
    {
        SwitchCameraView();
    }
}

void PlayerControllerComponent::Deserialize(const rapidjson::Value& value)
{
    if (value.HasMember("MoveSpeed"))
    {
        mMoveSpeed = value["MoveSpeed"].GetFloat();
    }
}
