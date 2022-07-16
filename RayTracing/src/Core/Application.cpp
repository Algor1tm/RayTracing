#include "Application.h"
#include "ImGui/ImGuiLayer.h"
#include "Debug.h"

#include <ImGui/imgui.h>


Application* Application::s_Instance = nullptr;

Application::Application()
	: m_Running(false)
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

	while (!m_Window->ShouldClose())
	{
		Time now = Timer.ElapsedTime();
		Time frameTime = now - LastTime;
		LastTime = now;

		for (auto& layer : m_LayerStack)
		{
			layer->OnUpdate(frameTime);
		}
		
		m_ImGuiLayer->Begin();
		for (auto& layer : m_LayerStack)
		{
			layer->OnImGuiRender();
		}
		m_ImGuiLayer->End();

		m_Window->OnUpdate();
	}

	m_Running = false;
}

void Application::PushLayer(Layer* layer)
{
	m_LayerStack.push_back(Layer::pointer_type(layer));
	layer->OnAttach();
}
