#pragma once
#include "TypeIds.h"
namespace SpringEngine
{
	class GameObject;

	class Componet
	{
	public:
		Componet() = default;
		virtual ~Componet() = default;

		Componet(const Componet&) = delete;
		Componet(const Componet&&) = delete;
		Componet& operator=(const Componet&) = delete;
		Componet& operator=(const Componet&&) = delete;

		virtual void Initialize() {}
		virtual void Terminate() {}
		virtual void Update(float deltaTime) {}
		virtual void DebugUI() {}

		virtual uint32_t GetTypeId() const = 0;

		GameObject& GetOwner() { return *mOwner; }
		const GameObject& GetOwner() const{ return *mOwner; }

		// serialize and deserialize
	private:
		friend class GameObject;
		GameObject* mOwner = nullptr;
	};
}
