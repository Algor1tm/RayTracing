#include "Environment.h"


Sphere::Sphere(float radius, const glm::vec3& center)
	: m_Radius(radius), m_Center(center)
{

}

bool Sphere::Intersect(const Ray& ray, glm::vec3& outPoint) const
{
	// (bx^2 + by^2 + bz^2)t^2 + 2(axbx + ayby + azbz - Oxbx - Oyby - Ozbz)t + (a - O)^2 - r^2) = 0
	// a - ray origin
	// b - ray direction
	// t - hit distance
	// O - shere centre
	// r - sphere radius

	// ax^2 + bx + c = 0
	float a = glm::dot(ray.Direction, ray.Direction);
	float half_b = glm::dot(ray.Direction, ray.Origin - m_Center);
	float c = glm::dot(ray.Origin - m_Center, ray.Origin - m_Center) - m_Radius * m_Radius;

	float D = half_b * half_b - a * c;

	if (D < 0)
		return false;

	float sqrtD = glm::sqrt(D);

	float root = (-half_b - sqrtD) / a;
	if (root <= Ray::MinLength || root >= Ray::MaxLength)
	{
		root = (-half_b + sqrtD) / a;
		if (root <= Ray::MinLength || root >= Ray::MaxLength)
			return false;
	}

	outPoint = ray.At(root);
	return true;
}

glm::vec3 Sphere::GetNormal(const glm::vec3& surfacePoint) const
{
	return glm::normalize(surfacePoint - m_Center);
}



Plane::Plane(const glm::vec3& normal, const glm::vec3& point)
	: m_Point(point)
{
	m_Normal = glm::normalize(normal);
}

bool Plane::Intersect(const Ray& ray, glm::vec3& outPoint) const
{
	float dot = glm::dot(ray.Direction, m_Normal);

	if (dot > -0.001f)
		return false;

	float distance = glm::dot(m_Normal, (m_Point - ray.Origin)) / dot;

	outPoint = ray.At(distance);
	return true;
}

glm::vec3 Plane::GetNormal(const glm::vec3& surfacePoint) const
{
	return m_Normal;
}
