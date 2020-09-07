#pragma once

#include "Core/Core.h"

#ifdef PLATFORM_WINDOWS

extern Voxel::Application* Voxel::CreateApplication();

int main(int argc, char** argv)
{
	Voxel::Log::Init();

	auto app = Voxel::CreateApplication();

	app->Run();

	delete app;
}

#endif