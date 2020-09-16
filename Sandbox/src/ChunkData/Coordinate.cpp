#include "Coordinate.h"

namespace Voxel
{
	int toLocalBlockIndex(const BlockPosition& position)
	{
		return position.y * (CHUNK_AREA) + position.z * CHUNK_SIZE + position.x;
	}

	ChunkPosition toChunkPosition(const BlockPosition& position)
	{
		int x = position.x;
		int y = position.y;
		int z = position.z;

		return {
			x < 0 ? ((x - CHUNK_SIZE) / CHUNK_SIZE) : (x / CHUNK_SIZE),
			y < 0 ? ((y - CHUNK_SIZE) / CHUNK_SIZE) : (y / CHUNK_SIZE),
			z < 0 ? ((z - CHUNK_SIZE) / CHUNK_SIZE) : (z / CHUNK_SIZE),
		};
	}

	BlockPosition toLocalBlockPosition(const BlockPosition& position)
	{
		int x = position.x;
		int y = position.y;
		int z = position.z;

		return { (CHUNK_SIZE + (x % CHUNK_SIZE)) % CHUNK_SIZE,
			(CHUNK_SIZE + (y % CHUNK_SIZE)) % CHUNK_SIZE,
			(CHUNK_SIZE + (z % CHUNK_SIZE)) % CHUNK_SIZE };
	}

	BlockPosition toGlobalBlockPosition(const BlockPosition& blockPosition, const ChunkPosition& localChunkPosition)
	{
		return { localChunkPosition.x * CHUNK_SIZE + blockPosition.x,
			localChunkPosition.y * CHUNK_SIZE + blockPosition.y,
			localChunkPosition.z * CHUNK_SIZE + blockPosition.z };
	}
}