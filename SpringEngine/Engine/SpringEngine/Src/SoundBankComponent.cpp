#include "Precompiled.h"
#include "SoundBankComponent.h"

#include "GameObject.h"

using namespace SpringEngine;
//using namespace SpringEngine::Audio;

void SoundBankComponent::Initialize()
{
	SoundEffectManager* sm = SoundEffectManager::Get();
	for (auto& data : mSoundEffects)
	{
		data.second.soundId = sm->Load(data.second.fileName);
	}
}

void SoundBankComponent::Terminate()
{
	SoundEffectManager* sm = SoundEffectManager::Get();
	for (auto& data : mSoundEffects)
	{
		sm->Stop(data.second.soundId);
	}
}

void SoundBankComponent::Deserialize(const rapidjson::Value& value)
{
	if (value.HasMember("SoundEffects"))
	{
		auto soundEffects = value["SoundEffects"].GetObj();
		for (auto& effect : soundEffects)
		{

			SoundEffectData& data = mSoundEffects[effect.name.GetString()];
			if (effect.value.HasMember("FileName"))
			{
				data.fileName = effect.value["FileName"].GetString();
			}
			if (effect.value.HasMember("Looping"))
			{
				data.isLooping = effect.value["Looping"].GetBool();
			}
		}
	}
}

void SoundBankComponent::DebugUI()
{
	std::string playButtonTag = "PlaySound##" + GetOwner().GetName();
	std::string stopButtonTag = "PlaySound##" + GetOwner().GetName();
	std::string soundEffectHeader = "SoundEffects##" + GetOwner().GetName();
	ImGui::Indent();
	if (ImGui::CollapsingHeader(soundEffectHeader.c_str()))
	{
		for (auto& data : mSoundEffects)
		{
			if (ImGui::CollapsingHeader(data.first.c_str()))
			{
				std::string buttonName = data.first + playButtonTag;
				if (ImGui::Button(buttonName.c_str()))
				{
					Play(data.first);
				}
				ImGui::SameLine();
				buttonName = data.first + stopButtonTag;
				if (ImGui::Button(buttonName.c_str()))
				{
					Stop(data.first);
				}
			}
		}
	}
	ImGui::Unindent();
}

void SoundBankComponent::Play(const std::string& key)
{
	auto data = mSoundEffects.find(key);
	if (data != mSoundEffects.end())
	{
		SoundEffectManager::Get()->Stop(data->second.soundId);
		SoundEffectManager::Get()->Play(data->second.soundId);
	}
}

void SoundBankComponent::Stop(const std::string& key)
{
	auto data = mSoundEffects.find(key);
	if (data != mSoundEffects.end())
	{
		SoundEffectManager::Get()->Stop(data->second.soundId);
	}
}

void SoundBankComponent::StopAll()
{
	SoundEffectManager* sm = SoundEffectManager::Get();
	for (auto data : mSoundEffects)
	{
		sm->Stop(data.second.soundId);
	}
}
