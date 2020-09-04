#pragma once

struct GLFWwindow;

namespace Voxel
{
	class GraphicsContext 
	{
	public:
		GraphicsContext(GLFWwindow* windowHandle);

		virtual void Init();
		virtual void SwapBuffers();
	private:
		GLFWwindow* m_WindowHandle;
	};
}