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
		m_BaseTexture = CreateRef<Texture>("assets/textures/Checkerboard.png");
		m_SpriteSheet = CreateRef<Texture>("assets/textures/farm.png");
		m_Dirt = SubTexture::CreateFromCoords(m_SpriteSheet, { 6, 11 }, { 128, 128 });
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

		//Renderer::DrawQuad(glm::mat4(1.0f), glm::vec4(1.0f, 0.0f, 0.5f, 1.0f));
		DrawCube(glm::translate(glm::mat4(1.0f), { 0.0f, 0.0f, 0.0f }), m_BaseTexture);
		DrawCube(glm::translate(glm::mat4(1.0f), { 0.0f, 2.0f, 0.0f }), m_BaseTexture);
		//Renderer::DrawQuad(glm::translate(glm::mat4(1.0f), { 0.0f,-1.0f, 0.0f }), m_Dirt);

		Renderer::EndScene();
	}

	void ApplicationLayer::OnEvent(Event& e)
	{
	}

	void ApplicationLayer::DrawCube(glm::mat4 transform, const Ref<Texture>& texture)
	{
		// Top, Bottom, Right, Left, Front, Back
		Renderer::DrawQuad(glm::translate(transform, { 0.0f, 0.5f, 0.0f }) * glm::rotate(glm::mat4(1.0f), -glm::radians(90.0f), { 1.0f, 0.0f, 0.0f }), texture);
		Renderer::DrawQuad(glm::translate(transform, { 0.0f,-0.5f, 0.0f }) * glm::rotate(glm::mat4(1.0f),  glm::radians(90.0f), { 1.0f, 0.0f, 0.0f }), texture);
		Renderer::DrawQuad(glm::translate(transform, { 0.5f, 0.0f, 0.0f }) * glm::rotate(glm::mat4(1.0f),  glm::radians(90.0f), { 0.0f, 1.0f, 0.0f }), texture);
		Renderer::DrawQuad(glm::translate(transform, {-0.5f, 0.0f, 0.0f }) * glm::rotate(glm::mat4(1.0f), -glm::radians(90.0f), { 0.0f, 1.0f, 0.0f }), texture);
		Renderer::DrawQuad(glm::translate(transform, { 0.0f, 0.0f, 0.5f }) * glm::rotate(glm::mat4(1.0f),  glm::radians(0.0f), { 0.0f, 1.0f, 0.0f }), texture);
		Renderer::DrawQuad(glm::translate(transform, { 0.0f, 0.0f,-0.5f }) * glm::rotate(glm::mat4(1.0f),  glm::radians(180.0f), { 0.0f, 1.0f, 0.0f }), texture);
	}


}