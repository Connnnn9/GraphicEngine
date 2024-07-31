#pragma once

#include"Componet.h"

namespace SpringEngine
{
	class TransformComponet final : public Componet, public Graphics::Transform
	{
	public:
		SET_TYPE_ID(ComponetId::Transform);

		void DebugUI() override;
	};
}