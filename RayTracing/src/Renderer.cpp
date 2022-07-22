#include "Renderer.h"
#include "Material.h"
#include "Random.h"


std::unique_ptr<Image> Renderer::m_FinalImage = nullptr;
std::vector<uint32_t> Renderer::m_ImageData = {};

std::shared_ptr<Scene> Renderer::m_Scene = nullptr;


void Renderer::Render(const std::shared_ptr<Scene>& scene)
{
	m_Scene = scene;

	for (uint32_t y = m_FinalImage->GetHeight() - 1; y > 0; --y)
	{
		for (uint32_t x = 0; x < m_FinalImage->GetWidth(); ++x)
		{
			uint32_t index = x + y * m_FinalImage->GetWidth();
			glm::vec4 color(0);

			for (uint32_t i = 0; i < RendererProps::SamplesPerPixel; ++i)
			{
				glm::vec2 coord = { 
					((float)x + Random::Float()) / (float)m_FinalImage->GetWidth(), 
					((float)y + Random::Float()) / (float)m_FinalImage->GetHeight() };
				color += FragmentShader(coord);
			}

			color /= RendererProps::SamplesPerPixel;
			m_ImageData[index] = RGBAtoHEX(color);
		}
	}

	m_FinalImage->SetData(m_ImageData.data(), sizeof(std::vector<uint32_t>::value_type) * m_ImageData.size());
}

void Renderer::OnResize(uint32_t width, uint32_t height)
{
	if (!m_FinalImage)
	{
		m_FinalImage = std::make_unique<Image>(width, height, ImageFormat::RGBA);
	}
	else
	{
		if (width == m_FinalImage->GetWidth() && height == m_FinalImage->GetHeight())
			return;
		m_FinalImage->Resize(width, height);
	}

	m_ImageData.resize(width * height);
}

glm::vec4 Renderer::FragmentShader(glm::vec2 coord)
{
	Ray ray = m_Scene->Camera.CastRay(coord);
	HitRecord record;
	glm::vec3 color(1);

	for (uint32_t i = 0; i < RendererProps::ChildRaysCount; ++i)
	{
		glm::vec3 attenuation;
		if (m_Scene->Objects.ShootRay(ray, &record))
		{
			if(!record.ObjectMaterial->Scatter(record, &ray, &attenuation))
				return glm::vec4(0, 0, 0, 1);

			color *= attenuation;
			continue;
		}

		glm::vec3 skyColor = glm::mix(glm::vec3(1.f), glm::vec3(0.5f, 0.7f, 1.f), 0.5f * (coord.y + 1));
		color *= skyColor;

		break;
	}

	return PostProcess(color);
}

glm::vec4 Renderer::PostProcess(const glm::vec3& color)
{
	glm::vec3 result;
	result = glm::clamp(color, 0.f, 1.f);
	result = glm::sqrt(result); // gamma correction
	return glm::vec4(color, 1);
}
