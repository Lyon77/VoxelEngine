#pragma once

#include "Renderer/Camera.h"
#include "Renderer/Texture.h"

namespace Voxel
{
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void OnWindowResize(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

		static void BeginScene(const Camera& camera, glm::mat4 transform);
		static void EndScene();
		static void Flush();
		static void Clear(glm::vec4 color);

		// Using Transforms instead of Vecs
		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
		static void DrawQuad(const glm::mat4& transform, const Ref<Texture>& texture, const glm::vec4& color = glm::vec4(1.0f), float textureScale = 1.0f);
		static void DrawQuad(const glm::mat4& transform, const Ref<SubTexture>& subtexture, const glm::vec4& color = glm::vec4(1.0f), float textureScale = 1.0f);

		struct Statistics
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GetTotalVertexCount() { return QuadCount * 4; };
			uint32_t GetTotalIndexCount() { return QuadCount * 6; };
		};

		static void ResetStats();
		static Statistics GetStats();

	private:
		static void FlushAndReset();
	};
}