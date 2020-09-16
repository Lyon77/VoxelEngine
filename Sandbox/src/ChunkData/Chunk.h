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

		ChunkPosition GetPosition() { return m_Position; }

		uint8_t GetBlock(const BlockPosition& position);
		void SetBlock(const BlockPosition& position, uint8_t type);
		bool IsSurrounded(const BlockPosition& position);

		void Fill(uint8_t value) { m_Blocks.fill(value); }

		void Render();
	private:
		void CreateMesh(glm::mat4 transform);

	private:
		std::array<uint8_t, CHUNK_VOLUME> m_Blocks{ 1 };

		ChunkPosition m_Position;
	};
}