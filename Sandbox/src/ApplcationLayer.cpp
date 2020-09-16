#include "ApplicationLayer.h"

#include <gl/GL.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>

#include "ChunkData/TerrainGen.h"

namespace Voxel
{
	ApplicationLayer::ApplicationLayer()
		: m_Camera(glm::perspectiveFov(glm::radians(45.0f), 1280.0f, 720.0f, 0.1f, 10000.0f))
	{
		new BlockManager();
		m_Chunk = CreateRef<Chunk>(glm::vec3(0.0f));
		makeStepTerrain(m_Chunk.get());
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
		//m_Chunk->Update(ts);

		// Clear
		Renderer::Clear(glm::vec4(0.6f, 0.6f, 1.0f, 1.0f));

		// Render
		Renderer::BeginScene(m_Camera, glm::mat4(1.0f));

		m_Chunk->Render();

		Renderer::EndScene();
	}

	void ApplicationLayer::OnEvent(Event& e)
	{
	}
}