#include "precompile.h"
#include "Core/Window.h"

#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"

namespace Voxel
{
	static uint32_t s_GLFWWindowCount = 0;

	static void GLFWErrorCallback(int error, const char* description) {
		VL_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Scope<Window> Window::Create(const WindowProps& props)
	{
		return CreateScope<Window>(props);
	}

	Window::Window(const WindowProps& props)
	{
		Init(props);
	}

	Window::~Window()
	{
		Shutdown();
	}

	void Window::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		//VL_CORE_INFO("Created window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (s_GLFWWindowCount == 0)
		{
			int success = glfwInit();
			CORE_ASSERT(success, "Count not initalize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
		}

		{
			m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
			++s_GLFWWindowCount;
		}

		m_Context = CreateScope<GraphicsContext>(static_cast<GLFWwindow*>(m_Window));
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		////Set GLFW callbacks
		//glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		//	{
		//		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		//		data.Width = width;
		//		data.Height = height;
		//
		//		//create a window event
		//		WindowResizeEvent event(width, height);
		//
		//		//dispatch it
		//		data.EventCallback(event);
		//	});
		//
		//glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
		//	WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		//	WindowCloseEvent event;
		//	data.EventCallback(event);
		//	});
		//
		//glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		//	{
		//		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		//
		//		//for the future, we might need to modify key into a Moza key for other platforms that don't use GLFW
		//		switch (action)
		//		{
		//		case GLFW_PRESS:
		//		{
		//			KeyPressedEvent event(key, 0);
		//			data.EventCallback(event);
		//			break;
		//		}
		//		case GLFW_RELEASE:
		//		{
		//			KeyReleasedEvent event(key);
		//			data.EventCallback(event);
		//			break;
		//		}
		//		case GLFW_REPEAT:
		//		{
		//			KeyPressedEvent event(key, 1);
		//			data.EventCallback(event);
		//			break;
		//		}
		//		}
		//	});
		//
		//glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
		//	{
		//		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		//		KeyTypedEvent event(keycode);
		//
		//		data.EventCallback(event);
		//	});
		//
		//glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		//	{
		//		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		//
		//		switch (action)
		//		{
		//		case GLFW_PRESS:
		//		{
		//			MouseButtonPressedEvent event(button);
		//			data.EventCallback(event);
		//			break;
		//		}
		//		case GLFW_RELEASE:
		//		{
		//			MouseButtonReleasedEvent event(button);
		//			data.EventCallback(event);
		//			break;
		//		}
		//		}
		//	});
		//
		//glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		//	{
		//		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		//
		//		MouseScrolledEvent event((float)xOffset, (float)yOffset);
		//		data.EventCallback(event);
		//	});
		//
		//glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		//	{
		//		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		//
		//		MouseMovedEvent event((float)xPos, (float)yPos);
		//		data.EventCallback(event);
		//	});
	}

	void Window::Shutdown()
	{
		glfwDestroyWindow(m_Window);
		--s_GLFWWindowCount;

		if (s_GLFWWindowCount == 0)
		{
			glfwTerminate();
		}
	}

	void Window::OnUpdate()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void Window::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.Vsync = enabled;
	}

	bool Window::IsVSync() const
	{
		return m_Data.Vsync;
	}

}