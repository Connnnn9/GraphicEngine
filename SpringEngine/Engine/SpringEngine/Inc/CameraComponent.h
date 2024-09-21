#pragma once

#include "Component.h"

namespace SpringEngine
{
	class CameraComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentId::Camera);

		void Initialize() override;
		void Terminate() override;
		virtual void Deserialize(const rapidjson::Value& value) override;

		Graphics::Camera& GetCamera();

		const Graphics::Camera& GetCamera() const;
		void SetFPSCamera(bool isFPS) { mIsFPSCamera = isFPS; }
		void SetFirstPersonCamera(bool isFirstPerson) { mIsFirstPersonCamera = isFirstPerson; }
		void SetThirdPersonCamera(bool isThirdPerson) { mIsThirdPersonCamera = isThirdPerson; }

	private:
		Graphics::Camera mCamera;
		bool mIsFPSCamera = false;
		bool mIsFirstPersonCamera = false;
		bool mIsThirdPersonCamera = false;
	};
}