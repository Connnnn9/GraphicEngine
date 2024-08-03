#pragma once

#include "GameObject.h"
#include "Service.h"

namespace SpringEngine
{
	class GameWorld final
	{
	public:
		void Initialize();
		void Terminate();

		void Update(float deltaTime);
		void Render();
		void DebugUI();

		void AddGameObject(GameObject* gameObject);
		void RemoveGameObject(GameObject* gameObject);


	private:
		using Services = std::vector<std::unique_ptr<Service>>;
		using GameObjects = std::vector<GameObject*>;

		Services mServices;
		GameObjects mGameObjects;
		GameObjects mPendingAddObjects;
		GameObjects mPendingRemoveObjects;

		bool mInitialized = false;
	};
}