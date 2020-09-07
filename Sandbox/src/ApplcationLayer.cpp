#include "ApplicationLayer.h"

#include <gl/GL.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Voxel
{
	ApplicationLayer::ApplicationLayer()
		: m_Camera(glm::perspectiveFov(glm::radians(45.0f), 1280.0f, 720.0f, 0.1f, 10000.0f))
	{

	}

	void ApplicationLayer::OnAttach()
	{
	}

	void ApplicationLayer::OnDetach()
	{
	}

	void ApplicationLayer::OnUpdate(Timestep ts)
	{
		// Update
		m_Camera.Update(ts);

		// Clear
		Renderer::Clear();

		// Render
		Renderer::BeginScene(m_Camera, glm::mat4(1.0f));

		Renderer::DrawQuad(glm::mat4(1.0f), glm::vec4(1.0f));

		Renderer::EndScene();
	}

	void ApplicationLayer::OnEvent(Event& e)
	{
	}


}