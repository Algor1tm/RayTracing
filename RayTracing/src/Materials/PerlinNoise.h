#pragma once

#include <glm/glm.hpp>

#include <vector>


class Perlin
{
public:
	Perlin(size_t pointCount = 256);

	float Turb(const glm::vec3& point, int depth = 7) const;
	float Noise(const glm::vec3& point) const;

private:
	std::vector<glm::ivec3> Generate() const;
	float PerlinInterp(glm::vec3 c[2][2][2], const glm::vec3& p) const;

private:
	std::vector<glm::vec3> m_Randoms;
	std::vector<glm::ivec3> m_Permutations;
	size_t m_Size;
};
