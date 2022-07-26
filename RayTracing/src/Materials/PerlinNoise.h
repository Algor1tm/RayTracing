#pragma once

#include <glm/glm.hpp>

#include <vector>


class Perlin
{
public:
	Perlin(size_t pointCount = 256);

	float Noise(const glm::vec3& point) const;

private:
	std::vector<glm::ivec3> Generate();

private:
	std::vector<float> m_Randoms;
	std::vector<glm::ivec3> m_Permutations;
	size_t m_Size;
};
