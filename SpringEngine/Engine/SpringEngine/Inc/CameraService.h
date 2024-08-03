#pragma once
#include "Service.h"

namespace SpringEngine
{
	class CameraService final : public Service
	{
	public:
		SET_TYPE_ID(ServiceId::Camera);

		void DebugUI() override;

		const Graphics::Camera& GetMain() const;
		void SetMainCamera(uint32_t index);
	private:
		friend class CameraComponet;
		void Register(const CameraComponet* cameraComponet);
		void UnRegister(const CameraComponet* cameraComponet);
		
		using CameraEntries = std::vector<const CameraComponet*>;
		CameraEntries mCameraEntries;
		const CameraComponet* mMainCamera = nullptr;
	};
}