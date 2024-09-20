#pragma once

#include "Component.h"
#include "CameraComponent.h"
#include "TransformComponent.h"

#include "TypeIds.h"

namespace SpringEngine
{
    class ThirdPersonCameraComponent : public Component
    {
    public:
        SET_TYPE_ID(ComponentId::ThirdPersonCamera);

        void Initialize() override;
        void Terminate() override;
        void Update(float deltaTime) override;

    private:
        CameraComponent* mCameraComponent = nullptr;
        TransformComponent* mPlayerTransform = nullptr;
        float mDistance = 5.0f;
        float mHeightOffset = 2.0f;
        float mYawSensitivity = 0.1f;
    };
}
