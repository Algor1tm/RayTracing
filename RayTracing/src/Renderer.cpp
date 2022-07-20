#include "Renderer.h"
#include "Random.h"


static uint32_t RGBAtoHEX(const glm::vec4& color)
{
	return ((uint32_t(color.a * 255) & 0xff) << 24) +
		((uint32_t(color.b * 255) & 0xff) << 16) +
		((uint32_t(color.g * 255) & 0xff) << 8) +
		((uint32_t(color.r * 255)) & 0xff);
}


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
		if (m_Scene->Objects.ShootRay(ray, &record))
		{
			color *= 0.5f;

			ray.Origin = record.Point;

			glm::vec3 rand = Random::InUnitSphere();
			rand = glm::dot(rand, record.Normal) > 0 ? rand : -rand;
			ray.Direction = record.Normal + rand;

			continue;
		}

		glm::vec3 skyColor = glm::mix(glm::vec3(1.f), glm::vec3(0.5f, 0.7f, 1.f), 0.5f * (coord.y + 1));
		color *= skyColor;
		color *= 0.5f;

		color = glm::clamp(color, 0.f, 1.f);
		color = glm::sqrt(color); // gamma correction
		return glm::vec4(color, 1);
	}

	return glm::vec4(0, 0, 0, 1);
}
