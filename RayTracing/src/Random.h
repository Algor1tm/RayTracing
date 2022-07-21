#pragma once

#include <random>

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>


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
		return glm::normalize(Vec3(-1.f, 1.f));
	}

private:
	static std::uniform_real_distribution<float> s_Distribution;
	static std::mt19937 s_RandomEngine;
};
