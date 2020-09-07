#pragma once

#include "Core/Core.h"
#include "Core/KeyCodes.h"
#include "Core/MouseButtonCodes.h"

namespace Voxel
{
	class Input
	{
	public:
		static bool IsKeyPressed(int keycode);

		static bool IsMouseButtonPressed(int button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}