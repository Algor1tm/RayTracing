#include "Texture.h"


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


glm::vec3 NoiseTexture::Value(glm::vec2 texCoords, const glm::vec3& point) const
{
	return glm::vec3(1.f) * m_Noise.Noise(point);
}
