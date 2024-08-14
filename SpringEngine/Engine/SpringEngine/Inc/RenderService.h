#pragma once

#include "Service.h"

namespace SpringEngine
{
	class CameraService;
	class Component;
	class MeshComponent;
	class TransformComponent;

	class RenderService final : public Service
	{
	public:
		SET_TYPE_ID(ServiceId::Render);

		void Initialize() override;
		void Terminate() override;
		void Update(float deltaTime) override;
		void Render() override;
		void DebugUI() override;

		void Register(const MeshComponent* meshComponent);
		void Unregister(const MeshComponent* meshComponent);
	private:
		const CameraService* mCameraService = nullptr;

		Graphics::DirectionalLight mDirectionalLight;
		Graphics::StandardEffect mStandardEffect;
		Graphics::ShadowEffect mShadowEffect;

		float mFPS = 0.0f;

		struct Entry
		{
			bool castShadow = true;
			const Component* renderComponent = nullptr;
			const TransformComponent* transformComponent = nullptr;
			Graphics::RenderGroup renderGroup;
		};

		using RenderEntries = std::vector<Entry>;
		RenderEntries mRenderEntries;
	};
}