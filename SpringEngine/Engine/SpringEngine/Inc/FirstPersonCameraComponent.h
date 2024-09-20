#pragma once

#include "Component.h"
#include "CameraComponent.h"
#include "TransformComponent.h"

#include "TypeIds.h"

namespace SpringEngine
{
    class FirstPersonCameraComponent : public Component
    {
    public:
        SET_TYPE_ID(ComponentId::FirstPersonCamera);

        void Initialize() override;
        void Terminate() override;
        void Update(float deltaTime) override;

    private:
        CameraComponent* mCameraComponent = nullptr;
        TransformComponent* mPlayerTransform = nullptr;
        float mHeightOffset = 1.8f;
        float mYawSensitivity = 0.1f;
    };
}
