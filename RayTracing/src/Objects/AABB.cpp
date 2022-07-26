#include "AABB.h"


AABB::AABB(const glm::vec3& min, const glm::vec3& max)
	: m_MinPoint(min), m_MaxPoint(max)
{

}

bool AABB::Intersect(const Ray& ray, float minLength, float maxLength) const
{
	for (int i = 0; i < 3; ++i)
	{
		float invD = 1.f / ray.Direction[i];

		float p0 = (m_MinPoint[i] - ray.Origin[i]) * invD;
		float p1 = (m_MaxPoint[i] - ray.Origin[i]) * invD;
		if (invD < 0.f)
			std::swap(p0, p1);

		float min = glm::max(p0, minLength);
		float max = glm::min(p1, maxLength);
		if (max <= min)
			return false;
	}

	return true;
}

AABB& AABB::Merge(const AABB& other)
{
	m_MinPoint = glm::min(m_MinPoint, other.m_MinPoint);
	m_MaxPoint = glm::max(m_MaxPoint, other.m_MaxPoint);

	return *this;
}
