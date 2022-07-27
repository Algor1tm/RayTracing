#include "Texture.h"
#include "Core/Debug.h"

#include <stb_image/stb_image.h>


SolidColor::SolidColor(const glm::vec3& color)
	: m_Color(color)
{

}

glm::vec3 SolidColor::Value(glm::vec2 texCoords, const glm::vec3& point) const
{
	return m_Color;
}


CheckerTexture::CheckerTexture(const glm::vec3& even, const glm::vec3& odd)
	: m_Even(std::make_shared<SolidColor>(even)), m_Odd(std::make_shared<SolidColor>(odd))
{

}

CheckerTexture::CheckerTexture(const std::shared_ptr<Texture>& even, const std::shared_ptr<Texture>& odd)
	: m_Even(even), m_Odd(odd)
{

}

glm::vec3 CheckerTexture::Value(glm::vec2 texCoords, const glm::vec3& point) const
{
	float sines = glm::sin(10.f * point.x) * glm::sin(10.f * point.y) * glm::sin(10.f * point.z);
	if (sines < 0)
		return m_Odd->Value(texCoords, point);
	else
		return m_Even->Value(texCoords, point);
}


NoiseTexture::NoiseTexture(float scale)
	: m_Scale(scale) 
{

}

glm::vec3 NoiseTexture::Value(glm::vec2 texCoords, const glm::vec3& point) const
{
	return glm::vec3(1.f) * 0.5f * (1 + glm::sin(m_Scale * point.z + 10 * m_Noise.Turb(point)));
}


ImageTexture::ImageTexture(const std::string& path)
{
	int width, height, channels;
	unsigned char* data;
	stbi_set_flip_vertically_on_load(1);

	data = stbi_load(path.data(), &width, &height, &channels, 3);
	ASSERT(data, "Failed to load image texture!");
	m_Width = width;
	m_Height = height;
	m_BytesPerPixel = channels;
	m_Data = reinterpret_cast<uint8_t*>(data);
}

ImageTexture::~ImageTexture()
{
	stbi_image_free(m_Data);
}

glm::vec3 ImageTexture::Value(glm::vec2 texCoords, const glm::vec3& point) const
{
	texCoords = glm::clamp(texCoords, 0.f, 1.f);

	int i = static_cast<int>(texCoords.x * m_Width);
	int j = static_cast<int>(texCoords.y * m_Height);
	if (i >= m_Width)  i = m_Width - 1;
	if (j >= m_Height) j = m_Height - 1;

	const float colorScale = 1.f / 255.f;
	uint8_t* pixel = m_Data + j * m_Width * m_BytesPerPixel + i * m_BytesPerPixel;

	return glm::vec3(colorScale * pixel[0], colorScale * pixel[1], colorScale * pixel[2]);
}
