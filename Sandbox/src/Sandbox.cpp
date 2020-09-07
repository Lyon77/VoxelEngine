#include <Voxel.h>
#include <Core/EntryPoint.h>

#include "ApplicationLayer.h"

class Sandbox : public Voxel::Application
{
public:
	Sandbox(const Voxel::ApplicationProps& props)
		: Application(props)
	{
		PushLayer(new Voxel::ApplicationLayer());
	}

	~Sandbox()
	{

	}
};


Voxel::Application* Voxel::CreateApplication()
{
	return new Sandbox({ "Sandbox", 1600, 900 });
}