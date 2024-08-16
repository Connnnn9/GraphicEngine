#include "Precompiled.h"
#include "ModelComponent.h"

using namespace SpringEngine;
using namespace SpringEngine::Graphics;

void SpringEngine::ModelComponent::Initialize()
{
	ModelManager* mm = ModelManager::Get();
	mModelId = mm->GetModelId(mFileName);
	if (mm->GetModel(mModelId)!= nullptr)
	{
		mModelId = mm->LoadModel(mFileName);
	}
	RenderObjectComponent::Initialize();
}

void SpringEngine::ModelComponent::Terminate()
{
	RenderObjectComponent::Terminate();
}

void SpringEngine::ModelComponent::Deserialize(const rapidjson::Value& value)
{
	RenderObjectComponent::Deserialize(value);
	if (value.HasMember("FileName"))
	{
		mFileName = value["FileName"].GetString();
	}
}

const Graphics::Model& SpringEngine::ModelComponent::GetModel() const
{
	return *ModelManager::Get()->GetModel(mModelId);
}
