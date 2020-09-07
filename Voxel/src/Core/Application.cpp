#include "precompile.h"
#include "Core/Application.h"

#include "Core/Log.h"

#include "Core/Input.h"

#include "Renderer/Renderer.h"

#include <imgui.h>

#include <Glad/glad.h>
#include <GLFW/glfw3.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <commdlg.h>

namespace Voxel
{
	Application* Application::s_Instance = nullptr;

	Application::Application(const ApplicationProps& props)
	{
		CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create(WindowProps(props.Name, props.WindowWidth, props.WindowHeight)));
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		//m_ImGuiLayer = new ImGuiLayer();
		//PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		Renderer::Shutdown();
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	std::string Application::OpenFile(const std::string& filter) const
	{
		OPENFILENAMEA ofn;

		CHAR szFile[260] = { 0 };

		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)m_Window->GetNativeWindow());
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = "All\0*.*\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (GetOpenFileNameA(&ofn) == TRUE)
			return ofn.lpstrFile;

		return std::string();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

		//events are triggered from the last layer to the first
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			//REWORD this line
			(*--it)->OnEvent(e);

			//if a layer interacts with event, make sure other layers don't interact with it
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			float time = (float)glfwGetTime(); // Platform::GetTime() in the future
			m_TimeStep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				//update each layer from begining to end
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(m_TimeStep);
			}

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(0, 0, e.GetWidth(), e.GetHeight());

		return false;
	}
}