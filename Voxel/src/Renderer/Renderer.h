#pragma once

#include "Renderer/Camera.h"

namespace Voxel
{
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera& camera, glm::mat4 transform);
		static void EndScene();
		static void Flush();

		// Using Transforms instead of Vecs
		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);

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