#pragma once

#include "Voxel.h"

namespace Voxel
{
	enum class VoxelType : uint8_t
	{
		Solid = 0,
		Fluid = 1,
		Flora = 2,
		Gas = 3,

		Error,
	};

	enum class BlockType : uint8_t
	{
		Air = 0,

		Grass,
		Dirt,
		Water,
		Stone,
		Wood,
		Sand,

		NumTypes
	};


	// Keep pretty skinny because we might instantiate a ton
	class Block
	{
	public:
		Block()
			: m_Active(true), m_BlockType(BlockType::Dirt), m_VoxelType(VoxelType::Solid)
		{
		}
		~Block() = default;

		bool IsActive() { return m_Active; }
		void SetActive(bool active) { m_Active = active; }

		BlockType GetBlockType() { return m_BlockType; }

	private:
		bool m_Active;

		VoxelType m_VoxelType;
		BlockType m_BlockType;
	};

	class BlockManager
	{
	public:
		BlockManager();

		void Render(BlockType type, glm::mat4 transform);

		inline static BlockManager& Get() { return *s_Instance; }
	private:
		void DrawCube(glm::mat4 transform, const Ref<SubTexture>& texture);
		void DrawCube(glm::mat4 transform, const Ref<SubTexture>& top, const Ref<SubTexture>& bottom, const Ref<SubTexture>& right, const Ref<SubTexture>& left, const Ref<SubTexture>& front, const Ref<SubTexture>& back);

	private:
		Ref<Texture> m_SpriteSheet;
		std::unordered_map<BlockType, Ref<SubTexture>> m_VoxelMap;

		static BlockManager* s_Instance;
	};
}