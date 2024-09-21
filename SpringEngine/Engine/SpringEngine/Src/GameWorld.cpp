#include "Precompiled.h"
#include "GameWorld.h"
#include "GameObjectFactory.h"

#include "CameraService.h"
#include "RenderService.h"
#include "UpdateService.h"
#include "UIRenderService.h"
#include "PhysicsService.h"

#include "TransformComponent.h"
#include "FirstPersonCameraComponent.h"
#include "ThirdPersonCameraComponent.h"
#include "CameraComponent.h"
#include "UISpriteComponent.h"
#include "UIButtonComponent.h"

using namespace SpringEngine;

namespace 
{
	CustomService TryService;
}
void GameWorld::SetCustomService(CustomService customService)
{
	TryService = customService;
}

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
	for (Slot& slot : mGameObjectSlots)
	{
		if (slot.gameObject != nullptr)
		{
			slot.gameObject->Terminate();
			slot.gameObject.reset();
		}
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

void GameWorld::LoadLevel(const std::filesystem::path& levelFile)
{
	FILE* file = nullptr;
	auto err = fopen_s(&file, levelFile.u8string().c_str(), "r");
	ASSERT(err == 0 && file != nullptr, "GameWorld: faild to load level %s", levelFile.u8string().c_str());

	char readBuffer[65536];
	rapidjson::FileReadStream readStream(file, readBuffer, sizeof(readBuffer));
	fclose(file);

	rapidjson::Document doc;
	doc.ParseStream(readStream);

	auto services = doc["Services"].GetObj();
	for (auto& service : services)
	{
		std::string serviceName = service.name.GetString();
		Service* newService = TryService(serviceName,*this);
		if (newService != nullptr)
		{
			LOG(" Custom Service %s was successfully added to the world", serviceName.c_str());
		}
		else if (serviceName == "CameraService")
		{
			newService = AddService<CameraService>();
		}
		else if (serviceName == "RenderService")
		{
			newService = AddService<RenderService>();
		}
		else if (serviceName == "UpdateService")
		{
			newService = AddService<UpdateService>();
		}
		else if (serviceName == "PhysicsService")
		{
			newService = AddService<PhysicsService>();
		}
		else if (serviceName == "UIRenderService")
		{
			newService = AddService<UIRenderService>();
		}
		else
		{
			ASSERT(false, "GameObject: service %s is not defined", serviceName.c_str());
		}
		ASSERT(newService != nullptr, "GameObject: service %s was not created properly", serviceName.c_str());
		newService->Deserialize(service.value);
	}
	uint32_t capacity = static_cast<uint32_t>(doc["Capacity"].GetInt());
	Initialize(capacity);

	if (doc["GameObjects"].HasMember("TestObject1"))
	{
		const char* playerTemplate = doc["GameObjects"]["TestObject1"]["Template"].GetString();
		GameObject* player = CreateGameObject(playerTemplate, "TestObject1");
		LOG("Creating Player: TestObject1");
		ASSERT(player != nullptr, "GameWorld: Failed to create player (TestObject1).");

		if (player != nullptr)
		{
			player->Initialize();
		}
	}


	auto gameobjects = doc["GameObjects"].GetObj();
	for (auto& gameObject : gameobjects)
	{
		std::string name = gameObject.name.GetString();
		const char* templateFile = gameObject.value["Template"].GetString();
		GameObject* obj = CreateGameObject(templateFile, name);

		LOG("Creating game object: %s", name.c_str());

		if (obj != nullptr)
		{
			if (gameObject.value.HasMember("TransformComponent"))
			{
				TransformComponent* transformComponent = obj->GetComponent<TransformComponent>();
				if (transformComponent != nullptr)
				{
					transformComponent->Deserialize(gameObject.value["TransformComponent"].GetObj());
				}
			}
			if (gameObject.value.HasMember("FirstPersonCameraComponent")) 
			{
				FirstPersonCameraComponent* firstPersonCamera = obj->GetComponent<FirstPersonCameraComponent>();
				if (firstPersonCamera != nullptr)
				{
					firstPersonCamera->Deserialize(gameObject.value["FirstPersonCameraComponent"].GetObj());
				}
			}
			if (gameObject.value.HasMember("ThirdPersonCameraComponent"))
			{
				ThirdPersonCameraComponent* thirdPersonCamera = obj->GetComponent<ThirdPersonCameraComponent>();
				if (thirdPersonCamera != nullptr)
				{
					thirdPersonCamera->Deserialize(gameObject.value["ThirdPersonCameraComponent"].GetObj());
				}
			}
			if (gameObject.value.HasMember("UISpriteComponent"))
			{
				UISpriteComponent* uiSpriteComponent = obj->GetComponent<UISpriteComponent>();
				if (uiSpriteComponent != nullptr)
				{
					uiSpriteComponent->Deserialize(gameObject.value["UISpriteComponent"].GetObj());
				}
			}
			if (gameObject.value.HasMember("UIButtonComponent"))
			{
				UIButtonComponent* uiButtonComponent = obj->GetComponent<UIButtonComponent>();
				if (uiButtonComponent != nullptr)
				{
					uiButtonComponent->Deserialize(gameObject.value["UIButtonComponent"].GetObj());
				}
			}
			if (gameObject.value.HasMember("CameraComponent"))
			{
				CameraComponent* cameraComponent = obj->GetComponent<CameraComponent>();
				if (cameraComponent != nullptr)
				{
					cameraComponent->Deserialize(gameObject.value["CameraComponent"].GetObj());
				}
			}
			obj->Initialize();
		}
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
	newObject->mHandle.mIndex = freeSlot;
	newObject->mHandle.mGeneration = slot.generation;

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

