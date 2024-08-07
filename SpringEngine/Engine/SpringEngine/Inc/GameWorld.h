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

		template<class ServiceType>
		ServiceType* AddService()
		{
			static_assert(std::is_base_of_v<Service, ServiceType>,
				"GameWorld: service must be of type Service");
			ASSERT(!mInitialized, "GameWorld: cant add a service after initialized");
			auto& newService = mServices.emplace_back(std::make_unique<ServiceType>());
			newService->mWorld = this;
			return static_cast<ServiceType*>(newService.get());
		}

		template<class ServiceType>
		const ServiceType* GetService() const
		{
			const GameWorld* thisConst = static_cast<const GameWorld*>(this);
			return const_cast<ServiceType*>(thisConst->GetService<ServiceType>());
		}

		template<class ServiceType>
		 ServiceType* GetService() 
		{
			 for (auto& service : mServices)
			 {
				 if (service->GetTypeId() == ServiceType::StaticGetTypeId())
				 {
					 return static_cast<ServiceType*>(service.get());
				 }
			 }
			 return nullptr;
		}

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