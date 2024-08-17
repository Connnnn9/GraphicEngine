#include "Precompiled.h"
#include "GameWorld.h"
#include "GameObjectFactory.h"

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

void SpringEngine::GameWorld::Initialize(uint32_t capacity)
{
	ASSERT(!mInitialized, "GameObject: is already initialized");

	for (auto& service : mServices)
	{
		service->Initialize();
	}
	mGameObjectSlots.resize(capacity);
	mFreeSlot.resize(capacity);
	std::iota(mFreeSlot.begin(), mFreeSlot.end(), 0);

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
	for (auto& service : mServices)
	{
		service->Update(deltaTime);
	}

	ProcessDestoryList();
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
	for (Slot& slot : mGameObjectSlots)
	{
		if (slot.gameObject != nullptr)
		{
			slot.gameObject->DebugUI();
		}
	}
	for (auto& service : mServices)
	{
		service->DebugUI();
	}
}

GameObject* SpringEngine::GameWorld::CreateGameObject(const std::filesystem::path& templateFile, const std::string& name)
{
	ASSERT(mInitialized, "GameWorld: is not initilized");

	if (mFreeSlot.empty())
	{
		ASSERT(false, "GameWorld: no free slots available");
		return nullptr;
	}

	const uint32_t freeSlot = mFreeSlot.back();
	mFreeSlot.pop_back();

	Slot& slot = mGameObjectSlots[freeSlot];
	std::unique_ptr<GameObject>& newObject = slot.gameObject;
	newObject = std::make_unique<GameObject>();
	GameObjectFactory::Make(templateFile, *newObject);
	std::string objName = name;
	newObject->SetName(objName);
	newObject->mWorld = this;
	newObject->mHandle.mGeneration = slot.generation;
	newObject->Initialize();

	return newObject.get();
}

GameObject* SpringEngine::GameWorld::GetGameObject(const std::string& name)
{
	GameObject* gameObject = nullptr;
	for (Slot& slot : mGameObjectSlots)
	{
		if (slot.gameObject != nullptr && slot.gameObject->GetName() == name)
		{
			gameObject = slot.gameObject.get();
			break;
		}
	}
	return gameObject;
}

GameObject* GameWorld::GetGameObject(const GameObjectHandle& handle)
{
	if (!IsValid(handle))
	{
		return nullptr;
	}
	return mGameObjectSlots[handle.mIndex].gameObject.get();
}

void GameWorld::DestoryGameObject(const GameObjectHandle& handle)
{
	if (!IsValid(handle))
	{
		return;
	}
	Slot& slot = mGameObjectSlots[handle.mIndex];
	slot.generation++;
	mToBeDestroyed.push_back(handle.mIndex);
}

bool GameWorld::IsValid(const GameObjectHandle& handle)
{
	if (handle.mIndex<0 || handle.mIndex>=mGameObjectSlots.size())
	{
		return false;
	}
	if (mGameObjectSlots[handle.mIndex].generation != handle.mGeneration)
	{

	return false;
	}
	return true;
}

void GameWorld::ProcessDestoryList()
{
	for (uint32_t index : mToBeDestroyed)
	{
		Slot& slot = mGameObjectSlots[index];

		GameObject* gameObject = slot.gameObject.get();
		ASSERT(!IsValid(gameObject->GetHandle()), "GameWorld : object is still alive");

		gameObject->Terminate();
		slot.gameObject.reset();
		mFreeSlot.push_back(index);
	}
	mToBeDestroyed.clear();
}

