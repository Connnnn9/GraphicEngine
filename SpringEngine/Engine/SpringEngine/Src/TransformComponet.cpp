#include "Precompiled.h"
#include "TransformComponet.h"

using namespace SpringEngine;
using namespace SpringEngine::Graphics;

void TransformComponet::DebugUI()
{
	SimpleDraw::AddTransform(GetMatrix4());
}
