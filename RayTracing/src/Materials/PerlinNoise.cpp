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
		m_Randoms[i] = glm::normalize(Random::Vec3(-1, 1));

	m_Permutations = Generate();
}

float Perlin::Turb(const glm::vec3& point, int depth) const
{
	float accum = 0.f;
	glm::vec3 temp_p = point;
	float weight = 1.f;

	for (int i = 0; i < depth; ++i)
	{
		accum += weight * Noise(temp_p);
		weight *= 0.5f;
		temp_p *= 2;
	}

	return glm::abs(accum);
}

float Perlin::Noise(const glm::vec3& point) const
{
	glm::vec3 p = point - glm::floor(point);

	glm::ivec3 indices = glm::floor(point);
	glm::vec3 c[2][2][2];
	for (size_t di = 0; di < 2; ++di)
	{
		for (size_t dj = 0; dj < 2; ++dj)
		{
			for (size_t dk = 0; dk < 2; ++dk)
			{
				c[di][dj][dk] = m_Randoms[
					m_Permutations[(indices.x + di) & 255].x ^ 
					m_Permutations[(indices.y + dj) & 255].y ^
					m_Permutations[(indices.z + dk) & 255].z];
			}
		}
	}

	return PerlinInterp(c, p);
}

float Perlin::PerlinInterp(glm::vec3 c[2][2][2], const glm::vec3& p) const
{
	glm::vec3 round = p * p * (glm::vec3(3) - 2.f * p);
	float accum = 0.f;

	for (size_t i = 0; i < 2; ++i)
	{
		for (size_t j = 0; j < 2; ++j)
		{
			for (size_t k = 0; k < 2; ++k)
			{
				glm::vec3 weights(p - glm::vec3(i, j, k));

				accum += (i * p.x + (1 - i) * (1 - p.x)) *
					(j * p.y + (1 - j) * (1 - p.y)) *
					(k * p.z + (1 - k) * (1 - p.z)) * 
					glm::dot(c[i][j][k], weights);
			}
		}
	}

	return accum;
}

std::vector<glm::ivec3> Perlin::Generate() const
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
