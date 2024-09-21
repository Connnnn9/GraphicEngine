#include "Precompiled.h"
#include "CameraService.h"

#include "CameraComponent.h"

using namespace SpringEngine;
using namespace SpringEngine::Graphics;

void CameraService::Initialize()
{
   
    mFPSCamera = nullptr;
    mFirstPersonCamera = nullptr;
    mThirdPersonCamera = nullptr;
    mMainCamera = nullptr;
    mIsUsingSpecialCamera = false;
    mIsFirstPersonView = true; 
}

void CameraService::Terminate()
{

    mMainCamera = nullptr;
    mFPSCamera = nullptr;
    mFirstPersonCamera = nullptr;
    mThirdPersonCamera = nullptr;

    mCameraEntries.clear();
}
void CameraService::DebugUI()
{
    SimpleDraw::Render(GetMain());

    if (ImGui::Begin("Camera Switch"))
    {
        if (ImGui::Button("Switch to FPS Camera"))
        {
            SwitchToFPSCamera();
        }
        if (ImGui::Button("Switch to Special Camera"))
        {
            SwitchToSpecialCamera();
        }

        if (mIsUsingSpecialCamera)
        {
            ImGui::Text("Using Special Camera");
            if (ImGui::Button("Switch to First Person"))
            {
                SwitchToFirstPerson();
            }
            if (ImGui::Button("Switch to Third Person"))
            {
                SwitchToThirdPerson();
            }
        }
        ImGui::End();
    }
}

const Camera& CameraService::GetMain() const
{
    ASSERT(mMainCamera != nullptr, "CameraService: has no main camera");
    return mMainCamera->GetCamera();
}

void CameraService::SetMainCamera(uint32_t index)
{
    if (index < mCameraEntries.size())
    {
        mMainCamera = mCameraEntries[index];
    }
}

void CameraService::Register(const CameraComponent* cameraComponent)
{
    mCameraEntries.push_back(cameraComponent);
    if (mMainCamera == nullptr)
    {
        mMainCamera = cameraComponent;
    }
}

void CameraService::UnRegister(const CameraComponent* cameraComponent)
{
    auto iter = std::find(mCameraEntries.begin(), mCameraEntries.end(), cameraComponent);
    if (iter != mCameraEntries.end())
    {
        if (mMainCamera == *iter)
        {
            mMainCamera = nullptr;
        }
        mCameraEntries.erase(iter);
        if (mMainCamera == nullptr && !mCameraEntries.empty())
        {
            mMainCamera = mCameraEntries.front();
        }
    }
}

void CameraService::SwitchToFPSCamera()
{
    mMainCamera = mFPSCamera;
    mIsUsingSpecialCamera = false;
}

void CameraService::SwitchToSpecialCamera()
{
    mMainCamera = mFirstPersonCamera;
    mIsUsingSpecialCamera = true;
    mIsFirstPersonView = true;
}
void CameraService::SwitchToFirstPerson()
{
    mMainCamera = mFirstPersonCamera;
    mIsFirstPersonView = true;
}

void CameraService::SwitchToThirdPerson()
{
    mMainCamera = mThirdPersonCamera;
    mIsFirstPersonView = false;
}

void CameraService::ToggleSpecialCameraView()
{
    if (mIsFirstPersonView)
    {
        SwitchToThirdPerson();
    }
    else
    {
        SwitchToFirstPerson();
    }
}

void CameraService::SetFirstPersonCamera(const CameraComponent* cameraComponent)
{
    mFirstPersonCamera = cameraComponent;
}

void CameraService::SetThirdPersonCamera(const CameraComponent* cameraComponent)
{
    mThirdPersonCamera = cameraComponent;
}

void CameraService::SetFPSCamera(const CameraComponent* cameraComponent)
{
    mFPSCamera = cameraComponent;
}
