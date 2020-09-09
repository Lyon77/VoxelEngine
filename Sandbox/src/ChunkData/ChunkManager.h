#pragma once

#include "Chunk.h"

namespace Voxel
{
	class ChunkManager
	{
	public:
		ChunkManager();
		~ChunkManager() = default;

		void Update(Timestep ts, glm::vec3 cameraPos, glm::vec3 cameraView);

	private:
		void UpdateAsyncChunker() {}
		 
		void UpdateLoadList() {}
		 
		void UpdateSetupList() {}
		 
		void UpdateRebuildList() {}
		 
		void UpdateFlagsList() {}
		 
		void UpdateUnloadList() {}
		 
		void UpdateVisibilityList(glm::vec3 cameraPos) {}

		void UpdateRenderList() {}

	private:
		glm::vec3 m_CameraPos, m_CameraView;
	};
}