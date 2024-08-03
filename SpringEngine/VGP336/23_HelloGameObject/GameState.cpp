#include"GameState.h"

using namespace SpringEngine;
using namespace SpringEngine::Graphics;
using namespace SpringEngine::Math;
using namespace SpringEngine::Input;

void GameState::Initialize()
{

	mDirectionalLight.direction = Math::Normalize({ 1.0f,-1.0f,1.0f });
	mDirectionalLight.ambient = { 0.5f,0.5f,0.5f,1.0f };
	mDirectionalLight.diffuse = { 0.8f,0.8f,0.8f,1.0f };
	mDirectionalLight.specular = { 1.0f,1.0f,1.0f,1.0f };

	
	mGameWorld.Initialize();

	mGameObject.AddComponet<TransformComponet>();
	CameraComponet* cc = mGameObject.AddComponet<CameraComponet>();
	mGameObject.AddComponet<FPSCameraComponet>();
	mGameObject.Initialize();
	std::string name = "GameObject1";
	mGameObject.SetName(name);

	mGameWorld.AddGameObject(&mGameObject);

	mStandardEffect.Initialize(L"../../Assets/Shaders/Standard.fx");
	mStandardEffect.SetCamera(cc->GetCamera());
	mStandardEffect.SetDirectionalLight(mDirectionalLight);

}
void GameState::Terminate()
{
	mStandardEffect.Terminate();
	mGameObject.Terminate();

	mGameWorld.Terminate();
}
void GameState::Update(const float deltaTime)
{
	mGameWorld.Update(deltaTime);
}
void GameState::Render()
{
	mGameWorld.Render();

	CameraComponet* cc = mGameObject.GetComponet<CameraComponet>();
	SimpleDraw::AddGroundPlane(10.0f, Colors::White);
	SimpleDraw::Render(cc->GetCamera());
}
void GameState::DebugUI()
{
	ImGui::Begin("Debug control", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		mGameWorld.Render();
	ImGui::End();
}