#pragma once

#include "Common.h"
#include "App.h"
#include "AppState.h"

#include "Particle.h"
#include "ParticleSystem.h"
#include "FireworkParticleSystem.h"

#include "Event.h"
#include "EventManager.h"

#include "GameObject.h"
#include "GameObjectHandle.h"
#include "GameWorld.h"
#include "GameObjectFactory.h"

// components
#include "Component.h"
#include "AnimatorComponent.h"
#include "CameraComponent.h"
#include "FPSCameraComponent.h"
#include "FirstPersonCameraComponent.h"
#include "MeshComponent.h"
#include "ModelComponent.h"
#include "PlayerControllerComponent.h"
#include "RenderObjectComponent.h"
#include "RigidBodyComponent.h"
#include "SoundBankComponent.h"
#include "SoundEffectComponent.h"
#include "TransformComponent.h"
#include "ThirdPersonCameraComponent.h"
#include "UIComponent.h"
#include "UIButtonComponent.h"
#include "UISpriteComponent.h"

// services
#include "Service.h"
#include "CameraService.h"
#include "RenderService.h"
#include "UpdateService.h"
#include "PhysicsService.h"
#include "PlayerControllerService.h"
#include "UIRenderService.h"

namespace SpringEngine
{
	App& MainApp();
}