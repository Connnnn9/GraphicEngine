#pragma once

#include "Component.h"

namespace SpringEngine
{
	class MeshComponent : public Component
	{
	public:
		SET_TYPE_ID(ComponentId::Mesh);

		void Initialize() override;
		void Terminate() override;
		void Deserialize(const rapidjson::Value& value) override;

		bool CanCastShaow() const;
		const Graphics::Model& GetModel() const;

	private:
		Graphics::Model mModel;
		bool mCastShaow = true;
	};
}