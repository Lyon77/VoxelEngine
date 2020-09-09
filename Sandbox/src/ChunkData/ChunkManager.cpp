#include "ChunkManager.h"


namespace Voxel
{
	ChunkManager::ChunkManager()
		: m_CameraPos(glm::vec3(1.0f)), m_CameraView(glm::vec3(1.0f))
	{
	}

	void ChunkManager::Update(Timestep ts, glm::vec3 cameraPos, glm::vec3 cameraView)
	{
		UpdateAsyncChunker();

		UpdateLoadList();

		UpdateSetupList();

		UpdateRebuildList();

		UpdateFlagsList();

		UpdateUnloadList();

		UpdateVisibilityList(cameraPos);

		if (m_CameraPos != cameraPos || m_CameraView != cameraView)
		{
			UpdateRenderList();
		}

		m_CameraPos = cameraPos;
		m_CameraView = cameraView;
	}
}