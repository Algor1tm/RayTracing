#pragma once

#include "Utils.h"

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>

#include <random>


class Random
{
public:
	Random() = delete;

	static void Init()
	{
		s_RandomEngine.seed(std::random_device()());
	}

	static float Float()
	{
		return s_Distribution(s_RandomEngine);
	}

	static glm::vec3 Vec3()
	{
		return glm::vec3(Float(), Float(), Float());
	}

	static glm::vec3 Vec3(float min, float max)
	{
		return glm::vec3(Float() * (max - min) + min, Float() * (max - min) + min, Float() * (max - min) + min);
	}

	static glm::vec3 InUnitSphere()
	{
		while (true)
		{
			glm::vec3 result = Vec3(-1.f, 1.f);
			if (IsNearZero(result)) continue;
			return glm::normalize(result);
		}
	}

	static glm::vec3 InUnitDisk()
	{
		while (true)
		{
			glm::vec3 result = glm::vec3(Float() * 2.f - 1.f, Float() * 2.f - 1.f, 0.f);
			if (glm::dot(result, result) >= 1.f)
				continue;
			return result;
		}
	}

private:
	static std::uniform_real_distribution<float> s_Distribution;
	static std::mt19937 s_RandomEngine;
};
