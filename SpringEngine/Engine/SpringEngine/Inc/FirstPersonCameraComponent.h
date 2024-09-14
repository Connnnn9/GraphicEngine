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
        const TransformComponent* mPlayerTransform = nullptr; 
        float mHeightOffset = 1.8f;
    };
}
