#pragma once

#include "Component.h"
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

    private:
        TransformComponent* mTransformComponent = nullptr;
        float mMoveSpeed = 5.0f;
    };;
}
