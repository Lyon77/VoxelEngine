#pragma once

#include "Chunk.h"
#include "Coordinate.h"

namespace Voxel
{
	struct ChunkPositionHash {
		// http://www.beosil.com/download/CollisionDetectionHashing_VMV03.pdf
		std::size_t operator()(const ChunkPosition& position) const
		{
			int x = position.x;
			int y = position.y;
			int z = position.z;

			return (x * 88339) ^ (y * 91967) ^ (z * 126323);
		}
	};

	/*template<typename T>
	using ChunkPositionMap = std::unordered_map<ChunkPosition, T>*/

	class ChunkManager
	{
	public:
		ChunkManager() = default;
		~ChunkManager() = default;

		Chunk& AddChunk(const ChunkPosition& chunkPosition);

		uint8_t GetBlock(const BlockPosition& blockPosition);
		void SetBlock(const BlockPosition& blockPosition, uint8_t block);

		bool HasChunk(const ChunkPosition& chunk) const;
		bool HasNeighbours(const ChunkPosition& chunkPosition) const;

	private:
		std::unordered_map<ChunkPosition, Chunk, ChunkPositionHash> m_Chunks;
	};
}