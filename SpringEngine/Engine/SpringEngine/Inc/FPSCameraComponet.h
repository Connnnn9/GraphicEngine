#pragma once

#include "Component.h"

namespace SpringEngine
{
	class CameraComponet;

	class FPSCameraComponet final : public Component
	{
	public:
		SET_TYPE_ID(ComponetId::FPSCamera);

		void Initialize() override;
		void Terminate() override;
		void Update(float deltaTime) override;

	private:
		CameraComponet* mCameraComponet = nullptr;
		float mShiftSpeed = 10.0f;
		float mMoveSpeed = 1.0f;
		float mTurnSpeed = 0.1f;
	};
}