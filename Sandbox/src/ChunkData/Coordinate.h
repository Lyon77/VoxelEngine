#pragma once
#include "Voxel.h"

namespace Voxel
{
	static const int CHUNK_SIZE = 16;
	static const int CHUNK_AREA = CHUNK_SIZE * CHUNK_SIZE;
	static const int CHUNK_VOLUME = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;

	constexpr int TEMP_WORLD_HEIGHT = 4;
	constexpr int TEMP_WORLD_SIZE = 12;

	using BlockPosition = glm::vec3;
	using ChunkPosition = glm::vec3;

	int toLocalBlockIndex(const BlockPosition& position);

	ChunkPosition toChunkPosition(const BlockPosition& position);
	BlockPosition toLocalBlockPosition(const BlockPosition& position);
	BlockPosition toGlobalBlockPosition(const BlockPosition& blockPosition,
		const ChunkPosition& localChunkPosition);
}