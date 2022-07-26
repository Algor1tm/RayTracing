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

	inline static float Float()
	{
		return s_Distribution(s_RandomEngine);
	}

	inline static float Float(float min, float max)
	{
		return Float() * (max - min) + min;
	}

	inline static int Int(int min, int max)
	{
		return static_cast<int>(glm::round(Float(min, max)));
	}

	inline static glm::vec3 Vec3()
	{
		return glm::vec3(Float(), Float(), Float());
	}

	inline static glm::vec3 Vec3(float min, float max)
	{
		return glm::vec3(Float(min, max), Float(min, max), Float(min, max));
	}

	inline static glm::ivec3 IVec3(int min, int max)
	{
		return glm::ivec3(Int(min, max), Int(min, max), Int(min, max));
	}

	inline static glm::vec3 InUnitSphere()
	{
		return glm::normalize(Vec3(-1.f, 1.f));
	}

	inline static glm::vec3 InUnitDisk()
	{
		while (true)
		{
			glm::vec3 result = glm::vec3(Float(-1.f, 1.f), Float(-1.f, 1.f), 0.f);
			if (glm::dot(result, result) >= 1.f)
				continue;
			return result;
		}
	}

private:
	static std::uniform_real_distribution<float> s_Distribution;
	static std::mt19937 s_RandomEngine;
};
