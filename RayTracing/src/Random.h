#pragma once

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

private:
	static std::uniform_real_distribution<float> s_Distribution;
	static std::mt19937 s_RandomEngine;
};
