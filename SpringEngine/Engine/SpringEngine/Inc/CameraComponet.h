#pragma once

#include "Component.h"

namespace SpringEngine
{
	class CameraComponet final : public Component
	{
	public:
		SET_TYPE_ID(ComponetId::Camera);

		void Initialize() override;
		void Terminate() override;

		Graphics::Camera& GetCamera();
		const Graphics::Camera& GetCamera() const;

	private:
		Graphics::Camera mCamera;
	};
}