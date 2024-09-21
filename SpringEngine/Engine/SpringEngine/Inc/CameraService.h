#pragma once
#include "Service.h"
#include "CameraComponent.h"

namespace SpringEngine
{
	class CameraService final : public Service
	{
	public:
		SET_TYPE_ID(ServiceId::Camera);

		void Initialize() override;
		void Terminate() override;
		void DebugUI() override;

		const Graphics::Camera& GetMain() const;
		void SetMainCamera(uint32_t index);

		// Camera switch functions
		void SwitchToFPSCamera();
		void SwitchToSpecialCamera();
		void SwitchToFirstPerson();
		void SwitchToThirdPerson();
		void ToggleSpecialCameraView();

		// Setter functions for specific cameras
		void SetFirstPersonCamera(const CameraComponent* cameraComponent);
		void SetThirdPersonCamera(const CameraComponent* cameraComponent);
		void SetFPSCamera(const CameraComponent* cameraComponent);

		bool IsUsingSpecialCamera() const { return mIsUsingSpecialCamera; }
		bool IsFirstPersonView() const { return mIsFirstPersonView; }

	private:
		friend class CameraComponent;

		void Register(const CameraComponent* cameraComponent);
		void UnRegister(const CameraComponent* cameraComponent);
		
		using CameraEntries = std::vector<const CameraComponent*>;
		CameraEntries mCameraEntries;

		const CameraComponent* mMainCamera = nullptr;
		const CameraComponent* mFPSCamera = nullptr;
		const CameraComponent* mFirstPersonCamera = nullptr;
		const CameraComponent* mThirdPersonCamera = nullptr;

		bool mIsUsingSpecialCamera = false;
		bool mIsFirstPersonView = true;
	};
}