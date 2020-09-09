#include "Chunk.h"

namespace Voxel
{
	Chunk::Chunk()
		: m_XPos(0), m_YPos(0)
	{
		m_PBlocks = new Block**[CHUNK_SIZE];
		
		for (int i = 0; i < CHUNK_SIZE; i++)
		{
			m_PBlocks[i] = new Block*[CHUNK_SIZE];
			
			for (int j = 0; j < CHUNK_SIZE; j++)
			{
				m_PBlocks[i][j] = new Block[CHUNK_SIZE];
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

	void Chunk::Update(Timestep ts)
	{
	}

	void Chunk::Render()
	{
		// Inital transform is the chuck transform
		CreateMesh(glm::translate(glm::mat4(1.0f), { m_XPos * CHUNK_SIZE, m_YPos * CHUNK_SIZE, 0.0f }));
	}

	void Chunk::CreateMesh(glm::mat4 transform)
	{
		for (int x = 0; x < CHUNK_SIZE; x++)
		{
			for (int y = 0; y < CHUNK_SIZE; y++)
			{
				for (int z = 0; z < CHUNK_SIZE; z++)
				{
					if (m_PBlocks[x][y][z].IsActive())
					{
						CreateCube(glm::translate(transform, { x, y, z }));
					}
				}
			}
		}
	}

	void Chunk::CreateCube(glm::mat4 transform)
	{
		// Top, Bottom, Right, Left, Front, Back
		Renderer::DrawQuad(glm::translate(transform, { 0.0f, 0.5f, 0.0f }) * glm::rotate(glm::mat4(1.0f), -glm::radians(90.0f), { 1.0f, 0.0f, 0.0f }), glm::vec4(1.0f));
		Renderer::DrawQuad(glm::translate(transform, { 0.0f,-0.5f, 0.0f }) * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), { 1.0f, 0.0f, 0.0f }), glm::vec4(1.0f));
		Renderer::DrawQuad(glm::translate(transform, { 0.5f, 0.0f, 0.0f }) * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), { 0.0f, 1.0f, 0.0f }), glm::vec4(1.0f));
		Renderer::DrawQuad(glm::translate(transform, { -0.5f, 0.0f, 0.0f }) * glm::rotate(glm::mat4(1.0f), -glm::radians(90.0f), { 0.0f, 1.0f, 0.0f }), glm::vec4(1.0f));
		Renderer::DrawQuad(glm::translate(transform, { 0.0f, 0.0f, 0.5f }) * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), { 0.0f, 1.0f, 0.0f }), glm::vec4(1.0f));
		Renderer::DrawQuad(glm::translate(transform, { 0.0f, 0.0f,-0.5f }) * glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), { 0.0f, 1.0f, 0.0f }), glm::vec4(1.0f));
	}
}