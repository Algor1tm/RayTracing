#include "PerlinNoise.h"
#include "Random.h"


static void Swap(glm::ivec3& left, glm::ivec3& right)
{
	std::swap(left.x, right.x);
	std::swap(left.y, right.y);
	std::swap(left.z, right.z);
}


Perlin::Perlin(size_t pointCount)
	: m_Size(pointCount)
{
	m_Randoms.resize(m_Size);
	for (size_t i = 0; i < m_Size; ++i)
		m_Randoms[i] = Random::Float();

	m_Permutations = Generate();
}

float Perlin::Noise(const glm::vec3& point) const
{
	glm::ivec3 indices = glm::ivec3(4.f * point) & 255;
	return m_Randoms[m_Permutations[indices.x].x ^ m_Permutations[indices.y].y ^ m_Permutations[indices.z].z];
}

std::vector<glm::ivec3> Perlin::Generate()
{
	std::vector<glm::ivec3> result(m_Size);

	for (size_t i = 0; i < m_Size; ++i)
		result[i] = glm::ivec3(i);

	for (size_t i = m_Size - 1; i > 0; --i)
	{
		int target = Random::Int(0, i);
		Swap(result[i], result[target]);
	}

	return result;
}
