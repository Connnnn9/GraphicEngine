#pragma once

#include"Component.h"

namespace SpringEngine
{
	class TransformComponet final : public Component, public Graphics::Transform
	{
	public:
		SET_TYPE_ID(ComponetId::Transform);

		void DebugUI() override;

		virtual void Deserialize(const rapidjson::Value& value) override;
	};
}