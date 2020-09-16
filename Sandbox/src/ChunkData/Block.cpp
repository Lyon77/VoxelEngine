#include "Block.h"

#include <gl/GL.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Voxel
{
	BlockManager* BlockManager::s_Instance = nullptr;

	BlockManager::BlockManager()
	{
		s_Instance = this;

		m_SpriteSheet = CreateRef<Texture>("assets/textures/MinecraftSpriteSheet.png");
		m_VoxelMap[BlockType::Dirt] = SubTexture::CreateFromCoords(m_SpriteSheet, { 2, 94 }, { 16, 16 });
	}

	void BlockManager::Render(BlockType type, glm::mat4 transform)
	{
		DrawCube(transform, m_VoxelMap[BlockType::Dirt]);
	}

	void BlockManager::DrawCube(glm::mat4 transform, const Ref<SubTexture>& texture)
	{
		DrawCube(transform, texture, texture, texture, texture, texture, texture);
	}

	void BlockManager::DrawCube(glm::mat4 transform, const Ref<SubTexture>& top, const Ref<SubTexture>& bottom, const Ref<SubTexture>& right, const Ref<SubTexture>& left, const Ref<SubTexture>& front, const Ref<SubTexture>& back)
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