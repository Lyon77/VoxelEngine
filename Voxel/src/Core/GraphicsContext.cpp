#include "precompile.h"
#include "Core/GraphicsContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h>

namespace Voxel
{
	GraphicsContext::GraphicsContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		CORE_ASSERT(m_WindowHandle, "Window Handle is null!")
	}

	void GraphicsContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		//load glad
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CORE_ASSERT(status, "Failed to initialize Glad");

		//VL_CORE_INFO("OpenGL Info:");
		//VL_CORE_INFO("  Vender:   {0}", glGetString(GL_VENDOR));
		//VL_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		//VL_CORE_INFO("  Version:  {0}", glGetString(GL_VERSION));

		#ifdef MZ_ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		MZ_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Moza requires at least OpenGL version 4.5!");
		#endif
	}

	void GraphicsContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}