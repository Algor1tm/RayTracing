#include "Core/Application.h"
#include "Core/Time.h"
#include "Image.h"

#include <glad/glad.h>
#include <ImGui/imgui.h>


class RayTracing : public Layer
{
	void OnAttach()
	{

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

		if(m_Image != nullptr)
			ImGui::Image((void*)(uint64_t)m_Image->GetTextureID(), {(float)m_Image->GetWidth(), (float)m_Image->GetHeight()});
		ImGui::End();
		ImGui::PopStyleVar();
	}

private:
	void Render()
	{
		Timer timer;

		if (m_Image == nullptr || m_ViewportWidth != m_Image->GetWidth() || m_ViewportHeight != m_Image->GetHeight())
		{
			m_Image = std::make_unique<Image>(m_ViewportWidth, m_ViewportHeight, ImageFormat::RGBA);
			m_ImageData.resize(m_ViewportWidth * m_ViewportHeight);
		}

		for (uint32_t i = 0; i < m_ImageData.size(); ++i)
		{
			m_ImageData[i] = 0xffff00ff;
		}

		m_Image->SetData(m_ImageData.data(), m_ImageData.size());

		m_LastRenderTime = timer.ElapsedTime();
	}

private:
	std::unique_ptr<Image> m_Image;
	std::vector<uint32_t> m_ImageData;

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
