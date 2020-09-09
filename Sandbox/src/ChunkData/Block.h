#pragma once

namespace Voxel
{
	enum class BlockType
	{
		BlockType_Default = 0,

		BlockType_Grass,
		BlockType_Dirt,
		BlockType_Water,
		BlockType_Stone,
		BlockType_Wood,
		BlockType_Sand,

		BlockType_NumTypes
	};


	// Keep pretty skinny because we might instantiate a ton
	class Block
	{
	public:
		Block()
			: m_Active(true), m_BlockType(BlockType::BlockType_Default)
		{
		}
		~Block() = default;

		bool IsActive() { return m_Active; }
		void SetActive(bool active) { m_Active = active; }

	private:
		bool m_Active;

		BlockType m_BlockType;
	};
}