#pragma once

#include "Voxel.h"

#include "ChunkData/Chunk.h"

namespace Voxel
{
	class ApplicationLayer : public Layer
	{
	public:
		ApplicationLayer();
		virtual ~ApplicationLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		//virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;
	private:
		void DrawCube(glm::mat4 transform, const Ref<Texture>& texture);
		void DrawCube(glm::mat4 transform, const Ref<Texture>& top, const Ref<Texture>& bottom, const Ref<Texture>& right, const Ref<Texture>& left, const Ref<Texture>& front, const Ref<Texture>& back);
		void DrawCube(glm::mat4 transform, const Ref<SubTexture>& texture);
		void DrawCube(glm::mat4 transform, const Ref<SubTexture>& top, const Ref<SubTexture>& bottom, const Ref<SubTexture>& right, const Ref<SubTexture>& left, const Ref<SubTexture>& front, const Ref<SubTexture>& back);

	private:
		Camera m_Camera;

		Ref<Texture> m_BaseTexture;
		Ref<Texture> m_SpriteSheet;
		
		Ref<SubTexture> m_DirtTop;
		Ref<SubTexture> m_DirtSide;
		Ref<SubTexture> m_DirtBottom;

		Ref<Chunk> m_Chunk;
	};
}