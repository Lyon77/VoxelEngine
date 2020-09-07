#pragma once

#include "Voxel.h"

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

		Ref<Texture> m_BaseTexture;
		Ref<Texture> m_SpriteSheet;
		Ref<SubTexture> m_Dirt;
	};
}