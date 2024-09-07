#pragma once

#include "UIComponent.h"

namespace SpringEngine
{
	enum class ButtonState
	{
		Default,
		Hover,
		Click,
		Disabled,
		Count
	};

	class UIButtonComponent : public UIComponent
	{
	public:
		SET_TYPE_ID(ComponentId::UIButton);
		
		void Initialize() override;
		void Terminate() override;
		void Update(float deltaTime) override;
		void Render() override;
		void Deserialize(const rapidjson::Value& value) override;
	private:

		void OnClick();

		RECT mRect = { 0,0,0,0 };
		DirectX::XMFLOAT2 mPosition = { 0.0f,0.0f };
		Graphics::UISprite mButtonStates[static_cast<uint32_t>(ButtonState::Count)];
		std::string mButtonStatesTexture[static_cast<uint32_t>(ButtonState::Count)];
		ButtonState mCurrentState = ButtonState::Default;
	};
}