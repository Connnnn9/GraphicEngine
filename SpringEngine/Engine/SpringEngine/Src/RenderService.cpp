#include "Precompiled.h"
#include "RenderService.h"

#include "GameWorld.h"

#include "CameraService.h"
#include "MeshComponent.h"
#include "TransformComponet.h"

using namespace SpringEngine;
using namespace SpringEngine::Graphics;

void RenderService::Initialize()
{
	mCameraService = GetWorld().GetService<CameraService>();

	mDirectionalLight.direction = Math::Normalize({ 1.0f,-1.0f,1.0f });
	mDirectionalLight.ambient = { 0.5f,0.5f,0.5f,1.0f };
	mDirectionalLight.diffuse = { 0.8f,0.8f,0.8f,1.0f };
	mDirectionalLight.specular = { 1.0f,1.0f,1.0f,1.0f };

	mShadowEffect.Initialize();
	mShadowEffect.SetDirectionalLight(mDirectionalLight);

	mStandardEffect.Initialize(L"../../Assets/Shaders/Standard.fx");
	mStandardEffect.SetDirectionalLight(mDirectionalLight);
	mStandardEffect.SetLightCamera(mShadowEffect.GetLightCamera());
	mStandardEffect.SetShadowMap(mShadowEffect.GetDepthMap());
}

void RenderService::Terminate()
{
	mStandardEffect.Terminate();
	mShadowEffect.Terminate();
}

void RenderService::Update(float deltaTime)
{
	mFPS = 1.0f / deltaTime;
}

void RenderService::Render()
{
	const Camera& camera = mCameraService->GetMain();
	mStandardEffect.SetCamera(camera);
	for (Entry& entry : mRenderEntries)
	{
		for (RenderObject& renderObject : entry.renderGroup)
		{
			renderObject.transform = *entry.transformComponent;
		}


		mShadowEffect.Begin();
			for (Entry& entry : mRenderEntries)
			{
				if (entry.castShadow)
				{
					DrawRenderGroup(mShadowEffect, entry.renderGroup);
				}
			}
		mShadowEffect.End();

		mStandardEffect.Begin();
		for (Entry& entry : mRenderEntries)
		{
			DrawRenderGroup(mStandardEffect, entry.renderGroup);
		}
		mStandardEffect.End();
	}
}

void RenderService::DebugUI()
{
	ImGui::Text("FPS: %F", mFPS);
	if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::DragFloat3("Direction", &mDirectionalLight.direction.x, 0.1f))
		{
			mDirectionalLight.direction = Math::Normalize(mDirectionalLight.direction);
		}

		ImGui::ColorEdit4("Ambient##Light", &mDirectionalLight.ambient.r);
		ImGui::ColorEdit4("Diffuse##Light", &mDirectionalLight.diffuse.r);
		ImGui::ColorEdit4("Specular##Light", &mDirectionalLight.specular.r);
	}
	mStandardEffect.DebugUI();
	mShadowEffect.DebugUI();
}

void RenderService::Register(const MeshComponent* meshComponent)
{
	Entry& entry = mRenderEntries.emplace_back();

	const GameObject& gameObject = meshComponent->GetOwner();
	entry.renderComponent = meshComponent;
	entry.transformComponent = gameObject.GetComponent<TransformComponet>();
	entry.castShadow = meshComponent->CanCastShaow();
	entry.renderGroup = CreateRenderGroup(meshComponent->GetModel());
}

void RenderService::Unregister(const MeshComponent* meshComponent)
{
	auto iter = std::find_if(mRenderEntries.begin(),
		mRenderEntries.end(),
		[&](const Entry& entry)
		{
			return entry.renderComponent == meshComponent;
		}
	);
	if (iter != mRenderEntries.end())
	{
		CleanupRenderGroup(iter->renderGroup);
		mRenderEntries.erase(iter);
	}
}
