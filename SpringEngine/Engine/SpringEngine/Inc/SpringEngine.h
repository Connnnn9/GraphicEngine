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
#include "GameWorld.h"

#include "CameraComponet.h"
#include "Component.h"
#include "FPSCameraComponet.h"
#include "MeshComponent.h"
#include "TransformComponet.h"

#include "Service.h"
#include "CameraService.h"
#include "RenderService.h"
#include "UpdateService.h"

namespace SpringEngine
{
	App& MainApp();
}