#pragma once

#include "Voxel.h"

#include "ChunkData/ChunkManager.h"

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
		Camera m_Camera;

		Ref<Chunk> m_Chunk;
	};
}