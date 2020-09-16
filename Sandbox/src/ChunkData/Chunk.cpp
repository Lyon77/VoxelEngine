#include "Chunk.h"

namespace Voxel
{
	Chunk::Chunk(const ChunkPosition& position)
		: m_Position(position)
	{
		m_PBlocks = new uint8_t**[CHUNK_SIZE];
		
		for (int i = 0; i < CHUNK_SIZE; i++)
		{
			m_PBlocks[i] = new uint8_t *[CHUNK_SIZE];
			
			for (int j = 0; j < CHUNK_SIZE; j++)
			{
				m_PBlocks[i][j] = new uint8_t[CHUNK_SIZE];
				for (int k = 0; k < CHUNK_SIZE; k++)
				{
					m_PBlocks[i][j][k] = 6;
				}
			}
		}
	}

	Chunk::~Chunk()
	{
		for (int i = 0; i < CHUNK_SIZE; i++)
		{
			for (int j = 0; j < CHUNK_SIZE; j++)
			{
				delete [] m_PBlocks[i][j];
			}

			delete[] m_PBlocks[i];
		}

		delete[] m_PBlocks;
	}

	uint8_t Chunk::GetBlock(const BlockPosition& position)
	{
		int x = position.x;
		int y = position.y;
		int z = position.z;

		return m_PBlocks[x][y][z];
	}

	void Chunk::SetBlock(const BlockPosition& position, uint8_t type)
	{
		int x = position.x;
		int y = position.y;
		int z = position.z;

		m_PBlocks[x][y][z] = type;
	}

	bool Chunk::IsSurrounded(const BlockPosition& position)
	{
		int x = position.x;
		int y = position.y;
		int z = position.z;

		// Check Surrounding blocks
		return (!((x == CHUNK_SIZE - 1 || !m_PBlocks[x + 1][y][z] != 0)
			|| (x == 0 || !m_PBlocks[x - 1][y][z] != 0)
			|| (y == CHUNK_SIZE - 1 || !m_PBlocks[x][y + 1][z] != 0)
			|| (y == 0 || !m_PBlocks[x][y - 1][z] != 0)
			|| (z == CHUNK_SIZE - 1 || !m_PBlocks[x][y][z + 1] != 0)
			|| (z == 0 || !m_PBlocks[x][y][z - 1] != 0)));
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
					if (m_PBlocks[x][y][z] != 0 && !IsSurrounded({ x, y, z }))
					{
						manager.Render((BlockType)m_PBlocks[x][y][z], glm::translate(transform, { x, y, z }));
					}
				}
			}
		}
	}
}