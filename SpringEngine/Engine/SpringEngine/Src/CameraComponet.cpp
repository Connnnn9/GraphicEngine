#include "Precompiled.h"
#include "CameraComponet.h"

using namespace SpringEngine;
using namespace SpringEngine::Graphics;

void CameraComponet::Initialize()
{
}

void CameraComponet::Terminate()
{

}

Camera& CameraComponet::GetCamera()
{
	return mCamera;
}

const Camera& CameraComponet::GetCamera() const
{
	return mCamera;
}
