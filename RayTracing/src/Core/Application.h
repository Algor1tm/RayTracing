#pragma once

#include "ImGui/ImGuiLayer.h"
#include "Window.h"

#include <vector>
#include <memory>
#include <functional>


class Application
{
public:
	Application();
	virtual ~Application();

	void Run();

	void PushLayer(Layer* layer);

	static inline Application& Get() { return *s_Instance; };
	inline Window& GetWindow() { return *m_Window; }

	void SetMenubarCallback(const std::function<void()>& menubarCallback) { m_MenubarCallback = menubarCallback; }

	void Close() { m_Running = false; }

private:
	std::unique_ptr<Window> m_Window;
	bool m_Running;
	std::vector<Layer::pointer_type> m_LayerStack;
	std::unique_ptr<ImGuiLayer> m_ImGuiLayer;
	std::function<void()> m_MenubarCallback;

private:
	static Application* s_Instance;
};

Application* CreateApplication();
