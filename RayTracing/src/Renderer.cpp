#include "Renderer.h"


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

	for (uint32_t y = 0; y < m_FinalImage->GetHeight(); ++y)
	{
		for (uint32_t x = 0; x < m_FinalImage->GetWidth(); ++x)
		{
			uint32_t index = x + y * m_FinalImage->GetWidth();
			glm::vec2 coord = { (float)x / (float)m_FinalImage->GetWidth(), (float)y / (float)m_FinalImage->GetHeight()};

			//coord = coord * 2.f - 1.f;
			//coord.x *= (float)m_FinalImage->GetWidth() / (float)m_FinalImage->GetHeight();

			m_ImageData[index] = RGBAtoHEX(FragmentShader(coord));
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

	glm::vec3 closestHit(Ray::MaxLength);
	bool isHit = false;
	glm::vec3 color;
	for (auto& object : m_Scene->Objects)
	{
		glm::vec3 hit;
		if (!object->Intersect(ray, hit))
			continue;

		if (hit.z < closestHit.z)
		{
			closestHit = hit;

			glm::vec3 normal = object->GetNormal(closestHit);
			return glm::vec4(0.5f * (normal + 1.f), 1);
			color = m_Scene->Light.GetColor(normal);
			isHit = true;
		}
	}

	if (!isHit)
	{
		glm::vec3 skyColor = glm::mix(glm::vec3(0.9f, 0.9f, 1.f), glm::vec3(0.5f, 0.7f, 1.f), 0.5f * (coord.y + 1));
		return glm::vec4(skyColor, 1);
	}

	color = glm::clamp(color, 0.f, 1.f);
	return glm::vec4(color, 1);
}
