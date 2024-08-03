#include "Precompiled.h"
#include "GameWorld.h"
using namespace SpringEngine;

void GameWorld::Initialize()
{
	ASSERT(!mInitialized, "GameObject: is already initialized");

	for (auto& service : mServices)
	{
		service->Initialize();
	}

	mInitialized = true;
}

void GameWorld::Terminate()
{
	if (!mInitialized)
	{
		return;
	}
	for (auto& service : mServices)
	{
		service->Terminate();
		service.reset();
	}
	mServices.clear();
	mInitialized = false;
}

void GameWorld::Update(float deltaTime)
{
	for (auto& gameObject : mPendingAddObjects)
	{
		if (std::find(mGameObjects.begin(),mGameObjects.end(),gameObject)== mGameObjects.end())
		{
			mGameObjects.push_back(gameObject);
		}
	}
	mPendingAddObjects.clear();

	for (auto& service : mServices)
	{
		service->Update(deltaTime);
	}

	for (auto& gameObject : mPendingRemoveObjects)
	{
		auto iter = std::find(mGameObjects.begin(), mGameObjects.end(), gameObject);
		if (iter != mGameObjects.end())
		{
			mGameObjects.erase(iter);
		}
	}
	mPendingRemoveObjects.clear();
}

void GameWorld::Render()
{
	for (auto& service : mServices)
	{
		service->Render();
	}
}

void GameWorld::DebugUI()
{
	for (auto& service : mServices)
	{
		service->DebugUI();
	}
}

void GameWorld::AddGameObject(GameObject* gameObject)
{
	mPendingAddObjects.push_back(gameObject);
}

void GameWorld::RemoveGameObject(GameObject* gameObject)
{
	mPendingRemoveObjects.push_back(gameObject);
}
