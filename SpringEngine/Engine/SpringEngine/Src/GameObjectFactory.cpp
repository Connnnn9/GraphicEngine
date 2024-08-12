#include "Precompiled.h"
#include "GameObjectFactory.h"

#include "GameObject.h"

//components
#include "TransformComponet.h"
#include "CameraComponet.h"
#include "FPSCameraComponet.h"
#include "MeshComponent.h"

using namespace SpringEngine;
namespace rj = rapidjson;

namespace
{
	using namespace SpringEngine;

	Component* AddComponet(const std::string& componentName, GameObject& gameObject)
	{
		Component* component = nullptr;
		if (componentName == "TransformComponent")
		{
			component = gameObject.AddComponent<TransformComponet>();
		}
		else if (componentName == "CameraComponet")
		{
			component = gameObject.AddComponent<CameraComponet>();
		}
		else if (componentName == "FPSCameraComponent")
		{
			component = gameObject.AddComponent<FPSCameraComponet>();
		}
	}
}