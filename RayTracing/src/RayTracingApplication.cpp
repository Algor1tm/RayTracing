#include "Core/Application.h"
#include "Renderer.h"
#include "Random.h"

#include <GLFW/glfw3.h>
#include <ImGui/imgui.h>

#include <Windows.h>


class RayTracing : public Layer
{
	void OnAttach() override
	{
		Random::Init();

		RendererProps props;
		props.ChildRaysCount = 12;
		props.SamplesPerPixel = 32;
		props.ThreadsCount = 5;//std::thread::hardware_concurrency();

		Renderer::Init(props);

		m_Scene = std::make_shared<Scene>();
		m_Scene->LoadPerlinNoiseScene();


		MakeMaximizedWindow();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.IniFilename = NULL;
		ImGui::LoadIniSettingsFromDisk("../../../../RayTracing/imgui.ini");
	}

	void OnDetach() override
	{
		// Renderer Shutdown must be first
		Renderer::Shutdown();
		if(m_RendererThread.joinable())
			m_RendererThread.join();
	}

	void OnUpdate(Time frameTime) override
	{
		m_TimeToUpdate += frameTime.AsSeconds();
	}

	void OnImGuiRender() override
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0, 0});
		ImGui::Begin("Viewport");

		uint32_t newWidth = (uint32_t)ImGui::GetContentRegionAvail().x;
		uint32_t newHeight = (uint32_t)ImGui::GetContentRegionAvail().y;

		const auto& finalImage = Renderer::GetFinalImage();
		if (finalImage != nullptr)
		{
			// Upload image into the GPU must be on this thread
			if (m_TimeToUpdate - m_UpdateInterval > 0)
			{
				Renderer::UpdateImage();
				m_TimeToUpdate = 0;
			}

			ImGui::Image(
				(void*)(uint64_t)finalImage->GetTextureID(),
				{ (float)finalImage->GetWidth(), (float)finalImage->GetHeight() },
				{ 0, 1 },
				{ 1, 0 });
		}

		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::Begin("Settings");
		ImGui::Text("Render Time: %.3fs", Renderer::GetRenderTime().AsSeconds());
		if (ImGui::Button("Render") && Renderer::GetCurrentState() == RendererState::Nothing)
		{
			if (newWidth != m_ViewportWidth || newHeight != m_ViewportHeight)
			{
				m_ViewportWidth = newWidth;
				m_ViewportHeight = newHeight;
				Resize();
			}

			Render();
		}
		ImGui::End();
	}

private:
	void Render()
	{
		if (m_RendererThread.joinable())
			m_RendererThread.join();
		m_RendererThread = std::thread(Renderer::Render, m_Scene);
	}

	void Resize()
	{
		m_Scene->Camera.OnResize((float)m_ViewportWidth / (float)m_ViewportHeight);
		Renderer::OnResize(m_ViewportWidth, m_ViewportHeight);
	}

	void MakeMaximizedWindow()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		RECT workArea;
		SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0);
		glfwSetWindowPos(window, workArea.left, workArea.top);
		glfwSetWindowSize(window, workArea.right - workArea.left, workArea.bottom - workArea.top);
	}

private:
	std::thread m_RendererThread;
	std::shared_ptr<Scene> m_Scene;

	uint32_t m_ViewportWidth = 0;
	uint32_t m_ViewportHeight = 0;

	float m_UpdateInterval = 0.05f;
	float m_TimeToUpdate = 0;
};


class RayTracingApplication : public Application
{
public:
	RayTracingApplication()
	{
		PushLayer(new RayTracing());
	}
};


Application* CreateApplication()
{
	Application* app = new RayTracingApplication();
	app->SetMenubarCallback([app]()
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit"))
				{
					app->Close();
				}
				ImGui::EndMenu();
			}
		});

	return app;
}
