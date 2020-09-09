#pragma once

#include "Voxel.h"
#include "Block.h"

#include <gl/GL.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Voxel
{
	class Chunk
	{
	public:
		Chunk();
		~Chunk();

		void Update(Timestep ts);

		void Render();

		static const int CHUNK_SIZE = 16;

	private:
		void CreateMesh(glm::mat4 transform);
		void CreateCube(glm::mat4 transform);

	private:
		Block*** m_PBlocks;

		int m_XPos, m_YPos;
	};
}