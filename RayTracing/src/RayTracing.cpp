#include "Core/Application.h"
#include "Core/Time.h"
#include "Renderer.h"

#include <glad/glad.h>
#include <ImGui/imgui.h>


class RayTracing : public Layer
{
	void OnAttach()
	{
		m_Scene = std::make_shared<Scene>();

		m_Scene->Objects.push_back(std::make_shared<Sphere>(0.5f, glm::vec3(0, 0, -2)));

		DirectionalLight light(glm::vec3(-0.5f, -0.75f, -1));
		light.Direction = glm::normalize(light.Direction);
		m_Scene->Light = light;
	}

	void OnDetach()
	{

	}

	void OnUpdate(Time frameTime)
	{

	}

	void OnImGuiRender()
	{
		ImGui::Begin("Settings");
		ImGui::Text("Last Render: %.3fms", m_LastRenderTime.AsMilliseconds());
		if (ImGui::Button("Render"))
		{
			Render();
		}
		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0, 0});
		ImGui::Begin("Viewport");

		m_ViewportWidth = (uint32_t)ImGui::GetContentRegionAvail().x;
		m_ViewportHeight = (uint32_t)ImGui::GetContentRegionAvail().y;

		auto& finalImage = Renderer::GetFinalImage();
		if (finalImage != nullptr)
		{
			ImGui::Image(
				(void*)(uint64_t)finalImage->GetTextureID(),
				{ (float)finalImage->GetWidth(), (float)finalImage->GetHeight() },
				{ 0, 1 },
				{ 1, 0 });
		}

		ImGui::End();
		ImGui::PopStyleVar();
	}

private:
	void Render()
	{
		Timer timer;

		Renderer::OnResize(m_ViewportWidth, m_ViewportHeight);
		Renderer::Render(m_Scene);

		m_LastRenderTime = timer.ElapsedTime();
	}

private:
	std::shared_ptr<Scene> m_Scene;

	uint32_t m_ViewportWidth = 0;
	uint32_t m_ViewportHeight = 0;

	Time m_LastRenderTime = 0;
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
