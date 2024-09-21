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
        void DebugUI() override;

        void Deserialize(const rapidjson::Value& value) override;

    private:
        CameraComponent* mCameraComponent = nullptr;
        const TransformComponent* mPlayerTransform = nullptr;
        Vector3 mTargetPosition = Vector3::Zero;
        float mHeightOffset = 1.8f;
        float mYawSensitivity = 0.1f;

        float mYaw = 0.0f;
        float mPitch = 0.0f;
        float mPitchSensitivity = 0.2f;

        float mMinPitch = -1.5f;  
        float mMaxPitch = 1.5f;
    };
}
