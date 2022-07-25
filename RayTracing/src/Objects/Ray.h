#pragma once

#include <glm/glm.hpp>

#include <memory>
#include <vector>


//defines in src/Material.h
class Material;


struct Ray
{
public:
	Ray(const glm::vec3& direction, const glm::vec3& origin = glm::vec3(0), float time = 0.f)
		: Direction(direction), Origin(origin), Time(time) {}

	inline glm::vec3 At(float distance) const
	{
		return Origin + Direction * distance;
	}

public:
	glm::vec3 Direction;
	glm::vec3 Origin;
	float Time;

public:
	static constexpr float MinLength = 0.001f;
	static constexpr float MaxLength = 1000.f;
};


struct HitRecord
{
public:
	inline void SetFaceNormal(const Ray& ray)
	{
		Inside = glm::dot(Normal, ray.Direction) > 0;
		Normal = Inside ? -Normal : Normal;
	}

public:
	glm::vec3 Point;
	float Distance;
	glm::vec3 Normal;
	bool Inside;
	std::shared_ptr<Material> ObjectMaterial;
};

