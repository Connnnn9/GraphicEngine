#pragma once

#include "Service.h"
#include "CameraService.h"
#include "PlayerControllerComponent.h"

#include "TypeIds.h"
namespace SpringEngine
{
    class PlayerControllerService final : public Service
    {
    public:
        SET_TYPE_ID(ServiceId::PlayerController);

        void Initialize() override;
        void Terminate() override;
        void Update(float deltaTime) override;

        void SwitchCameraView();

    private:
        const CameraService* mCameraService;
        PlayerControllerComponent* mPlayerController;
        bool mIsFirstPerson = true;
    };
}
