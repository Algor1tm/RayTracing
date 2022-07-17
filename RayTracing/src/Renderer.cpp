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

void Renderer::Render()
{
	for (uint32_t y = 0; y < m_FinalImage->GetHeight(); ++y)
	{
		for (uint32_t x = 0; x < m_FinalImage->GetWidth(); ++x)
		{
			uint32_t index = x + y * m_FinalImage->GetWidth();
			glm::vec2 coord = { (float)x / (float)m_FinalImage->GetWidth(), (float)y / (float)m_FinalImage->GetHeight()};
			m_ImageData[index] = RGBAtoHEX(FragmentShader(coord));;
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
	coord = coord * 2.f - 1.f;
	coord.x *= (float)m_FinalImage->GetWidth() / (float)m_FinalImage->GetHeight();

	glm::vec3 rayOrigin(0, 0, 2);
	glm::vec3 rayDirection(coord, -1.f);
	rayDirection = glm::normalize(rayDirection);

	float radius = 0.5f;

	// (bx^2 + by^2 + bz^2)t^2 + 2(axbx + ayby + azbz)t + (ax^2 + ay^2 + az^2 - r^2) = 0
	// a - ray origin
	// b - ray direction
	// r - sphere radius
	// t - hit distance

	// ax^2 + bx + c = 0
	float a = glm::dot(rayDirection, rayDirection);
	float b = 2 * glm::dot(rayOrigin, rayDirection);
	float c = glm::dot(rayOrigin, rayOrigin) - radius * radius;
	
	float D = b * b - 4.f * a * c;

	if (D >= 0)
		return glm::vec4(1, 0, 1, 1);
	
	return glm::vec4(0, 0, 0, 1);
}
