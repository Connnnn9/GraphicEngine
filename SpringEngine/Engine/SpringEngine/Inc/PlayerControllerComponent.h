#pragma once

#include "Component.h"
#include "FirstPersonCameraComponent.h"
//#include "ThirdPersonCameraComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"

#include "TypeIds.h"

namespace SpringEngine
{
    class PlayerControllerComponent : public Component
    {
    public:
        SET_TYPE_ID(ComponentId::PlayerController);

        void Initialize() override;
        void Terminate() override;
        void Update(float deltaTime) override;
        void Deserialize(const rapidjson::Value& value) override;

        void SwitchCameraView();

    private:
        const Graphics::Camera* mCamera = nullptr;
        TransformComponent* mTransformComponent = nullptr;
        bool mIsFirstPerson = true;

        float mMoveSpeed = 5.0f;  // Movement speed
    };
}
