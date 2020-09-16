#pragma once

#include "Voxel.h"
#include "Block.h"

#include <gl/GL.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Coordinate.h"

namespace Voxel
{
	class Chunk
	{
	public:
		Chunk(const ChunkPosition& position);
		~Chunk();

		uint8_t GetBlock(const BlockPosition& position);
		void SetBlock(const BlockPosition& position, uint8_t type);
		bool IsSurrounded(const BlockPosition& position);

		void Render();
	private:
		void CreateMesh(glm::mat4 transform);

	private:
		uint8_t*** m_PBlocks;

		ChunkPosition m_Position;
	};
}