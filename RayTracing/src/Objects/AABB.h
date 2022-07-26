#pragma once 

#include "Ray.h"
#include "Core/Debug.h"


class AABB
{
public:
	AABB() = default;
	AABB(const glm::vec3& min, const glm::vec3& max);

	bool Intersect(const Ray& ray, float minLength, float maxLength) const;
	
	AABB& Merge(const AABB& other);

	const glm::vec3& Min() const { return m_MinPoint; }
	const glm::vec3& Max() const { return m_MaxPoint; }

private:
	glm::vec3 m_MinPoint;
	glm::vec3 m_MaxPoint;
};

