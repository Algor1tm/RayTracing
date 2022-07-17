#include "Application.h"
#include "ImGui/ImGuiLayer.h"
#include "Debug.h"

#include <ImGui/imgui.h>


Application* Application::s_Instance = nullptr;

Application::Application()
	: m_Running(true)
{
	ASSERT(!s_Instance, "Application already exists!\n");

	s_Instance = this;

	m_Window = std::make_unique<Window>(1280, 720);

	m_ImGuiLayer = std::make_unique<ImGuiLayer>();
	m_ImGuiLayer->OnAttach();
}

Application::~Application() 
{

}

void Application::Run()
{
	Timer Timer;
	Time LastTime;

	while (m_Running)
	{
		Time now = Timer.ElapsedTime();
		Time frameTime = now - LastTime;
		LastTime = now;

		for (auto& layer : m_LayerStack)
		{
			layer->OnUpdate(frameTime);
		}
		
		m_ImGuiLayer->Begin();

		{
			static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

			// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
			// because it would be confusing to have two docking targets within each others.
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
			if (m_MenubarCallback)
				window_flags |= ImGuiWindowFlags_MenuBar;

			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

			// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
			// and handle the pass-thru hole, so we ask Begin() to not render a background.
			if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
				window_flags |= ImGuiWindowFlags_NoBackground;

			// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
			// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
			// all active windows docked into it will lose their parent and become undocked.
			// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
			// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin("DockSpace Demo", nullptr, window_flags);
			// Submit the DockSpace
			ImGuiIO& io = ImGui::GetIO();
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("OpenGLDockspace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			}

			if (m_MenubarCallback)
			{
				if (ImGui::BeginMenuBar())
				{
					m_MenubarCallback();
					ImGui::EndMenuBar();
				}
			}
			ImGui::End();
			ImGui::PopStyleVar();
			ImGui::PopStyleVar(2);
		}

		for (auto& layer : m_LayerStack)
		{
			layer->OnImGuiRender();
		}

		m_ImGuiLayer->End();

		m_Window->OnUpdate();

		if (m_Window->ShouldClose())
			m_Running = false;
	}
}

void Application::PushLayer(Layer* layer)
{
	m_LayerStack.push_back(Layer::pointer_type(layer));
	layer->OnAttach();
}
