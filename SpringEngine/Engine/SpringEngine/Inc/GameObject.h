#pragma once

#include "Componet.h"

namespace SpringEngine
{
	class GameObject final
	{
	public:
		GameObject() = default;
		void Initialize();
		void Terminate();
		void DebugUI();

		void SetName(std::string& name);
		const std::string& GetName() const;
		uint32_t GetUniqueId() const;
		
		template <class ComponetType>
		ComponetType* AddComponet()
		{
			static_cast<std::is_base_of_v<Componet,ComponetType>,
				"GameObject: ComponetType Must be of type Componet");
				ASSERT(!mInitialized, "GameObject: cannot add componets once initialized");
				ASSERT(!HasA<ComponetType>(), "GameObject: already has componets type");

				auto& newComponet = mComponets.emplace_back(std::make_unique<ComponetType>());
				newComponet->mOwner = this;
				return static_cast<ComponetType*>(newComponet.get());
		}
		template <class ComponetType>
		bool HasA()
		{

		}
		template <class ComponetType>
		const ComponetType* GetComponet() const
		{

		}
		template <class ComponetType>
		ComponetType* GetComponet()
		{
			return const_cast<ComponetType*>(GetComponet());
		}
	private:
		std::string mName = "EMPTY";
		bool mInitialized = false;
		uint32_t mUniqueId = 0;

		using Componets = std::vector<std::unique_ptr<Componet>>;
		Componets mComponets;
	};
}