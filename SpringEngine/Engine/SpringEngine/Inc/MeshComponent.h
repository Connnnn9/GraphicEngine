#pragma once

#include "RenderObjectComponent.h"

namespace SpringEngine
{
	class MeshComponent final : public RenderObjectComponent
	{
	public:
		SET_TYPE_ID(ComponentId::Mesh);

		void Deserialize(const rapidjson::Value& value) override;

		const Graphics::Model& GetModel() const override;

		void UpdateTransform(const Math::Vector3& newPosition) override;

	private:
		Graphics::Model mModel;
		Graphics::Transform mTransform;
		Math::Matrix4 mTransformMatrix;
	};
}