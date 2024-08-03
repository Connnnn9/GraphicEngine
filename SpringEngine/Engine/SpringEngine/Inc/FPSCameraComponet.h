#pragma once

#include "Componet.h"

namespace SpringEngine
{
	class CameraComponet;

	class FPSCameraComponet final : public Componet
	{
	public:
		SET_TYPE_ID(ComponetId::FPSCamera);

		void Initialize() override;
		void Terminate() override;
		void Update(float deltaTime) override;
	
	private:
		CameraComponet* mCameraComponet = nullptr;
		float mShiftSpeed;
		float mMoveSpeed;
		float mTurnSpeed;
	};
}