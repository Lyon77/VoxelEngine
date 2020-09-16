#include "Chunk.h"

namespace Voxel
{
	Chunk::Chunk(const ChunkPosition& position)
		: m_Position(position)
	{
	}

	Chunk::~Chunk()
	{
	}

	uint8_t Chunk::GetBlock(const BlockPosition& position)
	{
		return m_Blocks.at(toLocalBlockIndex(position));
	}

	void Chunk::SetBlock(const BlockPosition& position, uint8_t type)
	{
		int x = position.x;
		int y = position.y;
		int z = position.z;

		m_Blocks.at(toLocalBlockIndex(position)) = type;
	}

	bool Chunk::IsSurrounded(const BlockPosition& position)
	{
		int x = position.x;
		int y = position.y;
		int z = position.z;

		// Check Surrounding blocks
		return (!((x == CHUNK_SIZE - 1 || !m_Blocks.at(toLocalBlockIndex({ (x + 1), y, z })) != 0)
			|| (x == 0 || !m_Blocks.at(toLocalBlockIndex({ (x - 1), y, z })) != 0)
			|| (y == CHUNK_SIZE - 1 || !m_Blocks.at(toLocalBlockIndex({ x, (y + 1), z })) != 0)
			|| (y == 0 || !m_Blocks.at(toLocalBlockIndex({ x, (y - 1), z })) != 0)
			|| (z == CHUNK_SIZE - 1 || !m_Blocks.at(toLocalBlockIndex({ x, y, (z + 1) })) != 0)
			|| (z == 0 || !m_Blocks.at(toLocalBlockIndex({ x, y, (z - 1) })) != 0)));
	}

	void Chunk::Render()
	{
		// Inital transform is the chuck transform
		CreateMesh(glm::translate(glm::mat4(1.0f), { m_Position.x * CHUNK_SIZE, m_Position.y * CHUNK_SIZE, m_Position.y * CHUNK_SIZE }));
	}

	void Chunk::CreateMesh(glm::mat4 transform)
	{
		BlockManager manager = BlockManager::Get();
		for (int x = 0; x < CHUNK_SIZE; x++)
		{
			for (int y = 0; y < CHUNK_SIZE; y++)
			{
				for (int z = 0; z < CHUNK_SIZE; z++)
				{
					if (m_Blocks.at(toLocalBlockIndex({x, y, z})) != 0 && !IsSurrounded({ x, y, z }))
					{
						manager.Render((BlockType)m_Blocks.at(toLocalBlockIndex({ x, y, z })), glm::translate(transform, { x, y, z }));
					}
				}
			}
		}
	}
}