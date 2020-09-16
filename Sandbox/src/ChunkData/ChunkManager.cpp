#include "ChunkManager.h"

namespace Voxel
{
	Chunk& ChunkManager::AddChunk(const ChunkPosition& chunkPosition)
	{
		auto itr = m_Chunks.find(chunkPosition);
		if (itr == m_Chunks.cend()) {
			return m_Chunks.emplace(std::piecewise_construct, std::forward_as_tuple(chunkPosition), std::forward_as_tuple(chunkPosition)).first->second;
		}
		return itr->second;
	}

	uint8_t ChunkManager::GetBlock(const BlockPosition& blockPosition)
	{
		auto chunkPosition = toChunkPosition(blockPosition);
		auto itr = m_Chunks.find(chunkPosition);
		if (itr == m_Chunks.cend()) {
			return 0;
		}
		return itr->second.GetBlock(toLocalBlockPosition(blockPosition));
	}

	void ChunkManager::SetBlock(const BlockPosition& blockPosition, uint8_t block)
	{
		auto chunkPosition = toChunkPosition(blockPosition);
		auto itr = m_Chunks.find(chunkPosition);
		if (itr != m_Chunks.cend()) {
			itr->second.SetBlock(toLocalBlockPosition(blockPosition), block);
		}
	}

	bool ChunkManager::HasChunk(const ChunkPosition& chunk) const
	{
		return m_Chunks.find(chunk) != m_Chunks.cend();
	}

	bool ChunkManager::HasNeighbours(const ChunkPosition& chunkPosition) const
	{
		const auto& cp = chunkPosition;
		return HasChunk(chunkPosition) &&
			// Top
			HasChunk({ cp.x, cp.y + 1, cp.z }) &&
			// Bottom
			HasChunk({ cp.x, cp.y - 1, cp.z }) &&
			// Left
			HasChunk({ cp.x - 1, cp.y, cp.z }) &&
			// Right
			HasChunk({ cp.x + 1, cp.y, cp.z }) &&
			// Front
			HasChunk({ cp.x, cp.y, cp.z - 1 }) &&
			// Back
			HasChunk({ cp.x, cp.y, cp.z + 1 });
	}
}