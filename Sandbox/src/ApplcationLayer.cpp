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
		m_Chunk = CreateRef<Chunk>();
	}

	void ApplicationLayer::OnAttach()
	{
		m_BaseTexture = CreateRef<Texture>("assets/textures/Checkerboard.png");
		m_SpriteSheet = CreateRef<Texture>("assets/textures/MinecraftSpriteSheet.png");
		m_DirtTop = SubTexture::CreateFromCoords(m_SpriteSheet, { 0, 94 }, { 16, 16 });
		m_DirtSide = SubTexture::CreateFromCoords(m_SpriteSheet, { 3, 94 }, { 16, 16 });
		m_DirtBottom = SubTexture::CreateFromCoords(m_SpriteSheet, { 2, 94 }, { 16, 16 });
	}

	void ApplicationLayer::OnDetach()
	{
	}

	void ApplicationLayer::OnUpdate(Timestep ts)
	{
		// Update
		m_Camera.Update(ts);
		m_Chunk->Update(ts);

		// Clear
		Renderer::Clear(glm::vec4(0.6f, 0.6f, 1.0f, 1.0f));

		// Render
		Renderer::BeginScene(m_Camera, glm::mat4(1.0f));

		/*for (int x = -2; x <= 2; x++)
		{
			for (int y = -2; y <= 2; y++)
			{
				for (int z = -2; z <= 2; z++)
				{
					DrawCube(glm::translate(glm::mat4(1.0f), { x, y, z }), m_DirtTop, m_DirtBottom, m_DirtSide, m_DirtSide, m_DirtSide, m_DirtSide);
				}
			}
		}*/

		m_Chunk->Render();

		Renderer::EndScene();
	}

	void ApplicationLayer::OnEvent(Event& e)
	{
	}

	void ApplicationLayer::DrawCube(glm::mat4 transform, const Ref<Texture>& texture)
	{
		DrawCube(transform, texture, texture, texture, texture, texture, texture);
	}

	void ApplicationLayer::DrawCube(glm::mat4 transform, const Ref<Texture>& top, const Ref<Texture>& bottom, const Ref<Texture>& right, const Ref<Texture>& left, const Ref<Texture>& front, const Ref<Texture>& back)
	{
		// Top, Bottom, Right, Left, Front, Back
		Renderer::DrawQuad(glm::translate(transform, { 0.0f, 0.5f, 0.0f }) * glm::rotate(glm::mat4(1.0f), -glm::radians(90.0f), { 1.0f, 0.0f, 0.0f }), top);
		Renderer::DrawQuad(glm::translate(transform, { 0.0f,-0.5f, 0.0f }) * glm::rotate(glm::mat4(1.0f),  glm::radians(90.0f), { 1.0f, 0.0f, 0.0f }), bottom);
		Renderer::DrawQuad(glm::translate(transform, { 0.5f, 0.0f, 0.0f }) * glm::rotate(glm::mat4(1.0f),  glm::radians(90.0f), { 0.0f, 1.0f, 0.0f }), right);
		Renderer::DrawQuad(glm::translate(transform, {-0.5f, 0.0f, 0.0f }) * glm::rotate(glm::mat4(1.0f), -glm::radians(90.0f), { 0.0f, 1.0f, 0.0f }), left);
		Renderer::DrawQuad(glm::translate(transform, { 0.0f, 0.0f, 0.5f }) * glm::rotate(glm::mat4(1.0f),  glm::radians(0.0f), { 0.0f, 1.0f, 0.0f }), front);
		Renderer::DrawQuad(glm::translate(transform, { 0.0f, 0.0f,-0.5f }) * glm::rotate(glm::mat4(1.0f),  glm::radians(180.0f), { 0.0f, 1.0f, 0.0f }), back);
	}

	void ApplicationLayer::DrawCube(glm::mat4 transform, const Ref<SubTexture>& texture)
	{
		DrawCube(transform, texture, texture, texture, texture, texture, texture);
	}

	void ApplicationLayer::DrawCube(glm::mat4 transform, const Ref<SubTexture>& top, const Ref<SubTexture>& bottom, const Ref<SubTexture>& right, const Ref<SubTexture>& left, const Ref<SubTexture>& front, const Ref<SubTexture>& back)
	{
		// Top, Bottom, Right, Left, Front, Back
		Renderer::DrawQuad(glm::translate(transform, { 0.0f, 0.5f, 0.0f }) * glm::rotate(glm::mat4(1.0f), -glm::radians(90.0f), { 1.0f, 0.0f, 0.0f }), top);
		Renderer::DrawQuad(glm::translate(transform, { 0.0f,-0.5f, 0.0f }) * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), { 1.0f, 0.0f, 0.0f }), bottom);
		Renderer::DrawQuad(glm::translate(transform, { 0.5f, 0.0f, 0.0f }) * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), { 0.0f, 1.0f, 0.0f }), right);
		Renderer::DrawQuad(glm::translate(transform, { -0.5f, 0.0f, 0.0f }) * glm::rotate(glm::mat4(1.0f), -glm::radians(90.0f), { 0.0f, 1.0f, 0.0f }), left);
		Renderer::DrawQuad(glm::translate(transform, { 0.0f, 0.0f, 0.5f }) * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), { 0.0f, 1.0f, 0.0f }), front);
		Renderer::DrawQuad(glm::translate(transform, { 0.0f, 0.0f,-0.5f }) * glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), { 0.0f, 1.0f, 0.0f }), back);
	}


}