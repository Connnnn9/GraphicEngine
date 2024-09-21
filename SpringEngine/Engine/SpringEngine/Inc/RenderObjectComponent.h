#pragma once

#include "Component.h"

namespace SpringEngine
{
	class RenderObjectComponent : public Component
	{
	public:
		void Initialize() override;
		void Terminate() override;

		void Deserialize(const rapidjson::Value& value) override;

		virtual void UpdateTransform(const Math::Vector3& newPosition) = 0;

		bool CastShadow() const;

		virtual Graphics::ModelId GetModelId() const { return 0; }
		virtual const Graphics::Model& GetModel() const = 0;


	private:
		bool mCastShadow = true;
	};
}