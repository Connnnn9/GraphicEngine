#include"GameState.h"

using namespace SpringEngine;
using namespace SpringEngine::Graphics;
using namespace SpringEngine::Math;
using namespace SpringEngine::Input;

void GameState::Initialize()
{

	CameraService* cs =  mGameWorld.AddService<CameraService>();
	mGameWorld.AddService<UpdateService>();
	mGameWorld.AddService<RenderService>();
	mGameWorld.Initialize(50);

	mGameWorld.CreateGameObject("../../Assets/Templates/fps_camera.json","Camera");
	mGameWorld.CreateGameObject("../../Assets/Templates/test_model.json","obj");
	mGameWorld.CreateGameObject("../../Assets/Templates/test_model2.json","obj2");
}
void GameState::Terminate()
{
	mGameWorld.Terminate();
}
void GameState::Update(const float deltaTime)
{
	mGameWorld.Update(deltaTime);
}
void GameState::Render()
{
	mGameWorld.Render();
}
void GameState::DebugUI()
{
	SimpleDraw::AddGroundPlane(10.0f, Colors::White);
	ImGui::Begin("Debug control", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		mGameWorld.DebugUI();
	ImGui::End();
}