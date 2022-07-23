#pragma once

#include <glm/glm.hpp>


#define EPSILON 1e-6f

constexpr bool IsNearZero(const glm::vec3& vec)
{
	return glm::all(glm::lessThan(glm::abs(vec), glm::vec3(EPSILON)));
}


constexpr uint32_t RGBAtoHEX(const glm::vec4& color)
{
	return ((uint32_t(color.a * 255) & 0xff) << 24) +
		((uint32_t(color.b * 255) & 0xff) << 16) +
		((uint32_t(color.g * 255) & 0xff) << 8) +
		((uint32_t(color.r * 255)) & 0xff);
}
