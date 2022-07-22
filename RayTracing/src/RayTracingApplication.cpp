#include "Core/Application.h"
#include "Core/Time.h"
#include "Renderer.h"
#include "Random.h"
#include "Material.h"

#include <glad/glad.h>
#include <ImGui/imgui.h>


class RayTracing : public Layer
{
	void OnAttach()
	{
		Random::Init();

		CameraOrientation orientation;
		orientation.Position = { 0, 0, 1 };
		orientation.LookAt = { 0, 0, -3 };
		orientation.Up = { 0, 1, 0 };

		CameraProps properties;
		properties.AspectRatio = 0; // viewport have not initialized yet
		properties.FOV = glm::radians(45.f);
		properties.FocusDist = glm::length(orientation.Position - orientation.LookAt);
		properties.LensRadius = 0.f;

		ProjectionCamera camera(orientation, properties);

		m_Scene = std::make_shared<Scene>(camera);

		const auto& planeMaterial = std::make_shared<Lambertian>(glm::vec3(0.4f, 0.4f, 0.4f));
		const auto& lambertianMaterial = std::make_shared<Lambertian>(glm::vec3(0.7f, 0.3f, 0.3f));
		const auto& dielectricMaterial = std::make_shared<Dielectric>(1.5f);
		const auto& metalMaterial = std::make_shared<Metal>(glm::vec3(0.8f, 0.8f, 0.2f));

		//m_Scene->Objects.Add(std::make_shared<Plane>(glm::vec3(0, 1, 0), glm::vec3(0, -0.51f, 0), planeMaterial));
		m_Scene->Objects.Add(std::make_shared<Sphere>(100.f, glm::vec3(0, -100.45f, 0), planeMaterial));
		m_Scene->Objects.Add(std::make_shared<Sphere>(0.5f, glm::vec3(0.f, -0.f, -3), lambertianMaterial));
		m_Scene->Objects.Add(std::make_shared<Sphere>(0.5f, glm::vec3(1.f, 0, -3), metalMaterial));
		m_Scene->Objects.Add(std::make_shared<Sphere>(0.5f, glm::vec3(-1.f, 0, -3), dielectricMaterial));
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
		ImGui::Text("Render Time: %.3fms", m_LastRenderTime.AsMilliseconds());
		if (ImGui::Button("Render"))
		{
			Render();
		}
		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0, 0});
		ImGui::Begin("Viewport");

		uint32_t newWidth = (uint32_t)ImGui::GetContentRegionAvail().x;
		uint32_t newHeight = (uint32_t)ImGui::GetContentRegionAvail().y;
		if (newWidth != m_ViewportWidth || newHeight != m_ViewportHeight)
		{
			m_ViewportWidth = newWidth;
			m_ViewportHeight = newHeight;
			Resize();
		}

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

		Renderer::Render(m_Scene);

		m_LastRenderTime = timer.ElapsedTime();
	}

	void Resize()
	{
		m_Scene->Camera.OnResize((float)m_ViewportWidth / (float)m_ViewportHeight);
		Renderer::OnResize(m_ViewportWidth, m_ViewportHeight);
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
