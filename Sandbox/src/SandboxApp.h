#pragma once

#include "Voxel.h"
#include "Core/EntryPoint.h"

#include <iostream>
#include <GLFW\glfw3.h>

void OnUpdate(Voxel::Timestep ts, Voxel::Camera camera)
{
	using namespace Voxel;

	// Clear
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// Render
	Renderer::BeginScene(camera, glm::mat4(1.0f));

	Renderer::DrawQuad(glm::mat4(1.0f), glm::vec4(1.0f));

	Renderer::EndScene();
}

int main(int argc, char** argv)
{
	using namespace Voxel;

	Window window = Window(WindowProps("Sandbox"));

	float lastFrameTime = 0;
	float aspectRatio = 1280.0f / 720.0f;
	float zoomLevel = 1.0f;
	Camera camera(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);

	Renderer::Init();

	while (true)
	{
		float time = (float)glfwGetTime(); // Platform::GetTime() in the future
		Timestep timestep = time - lastFrameTime;
		lastFrameTime = time;

		OnUpdate(timestep, camera);

		window.OnUpdate();
	}
}