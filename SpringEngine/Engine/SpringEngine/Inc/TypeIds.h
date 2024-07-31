#pragma once

namespace SpringEngine
{
	enum class ComponetId
	{
		Invalid,
		Transform,
		Camera,
		Count
	};
}

#define SET_TYPE_ID(id)\
static uint32_t StaticGetTypeId(){return static_cast<uint32_t>(id);}\
uint32_t GetTypeId() const override{return StaticGetTypeId();}