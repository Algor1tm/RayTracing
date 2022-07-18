#include "Environment.h"


Sphere::Sphere(float radius, const glm::vec3& center)
	: m_Radius(radius), m_Center(center)
{

}

bool Sphere::GetIntersectionPoint(const Ray& ray, glm::vec3& outPoint) const
{
	// (bx^2 + by^2 + bz^2)t^2 + 2(axbx + ayby + azbz - Oxbx - Oyby - Ozbz)t + (ax^2 + ay^2 + az^2 + Ox^2 + Oy^2 + Oz^2 - r^2) = 0
	// a - ray origin
	// b - ray direction
	// t - hit distance
	// O - shere centre
	// r - sphere radius

	// ax^2 + bx + c = 0
	float a = glm::dot(ray.Direction, ray.Direction);
	float b = 2 * (glm::dot(ray.Origin, ray.Direction) - glm::dot(m_Center, ray.Direction));
	float c = glm::dot(ray.Origin, ray.Origin) + glm::dot(m_Center, m_Center) - m_Radius * m_Radius;

	float D = b * b - 4.f * a * c;

	if (D < 0)
		return false;

	float t = (-b - std::sqrt(D)) / (2 * a);

	outPoint = ray.GetPoint(t);
	return true;
}

glm::vec3 Sphere::GetNormal(const glm::vec3& surfacePoint) const
{
	return glm::normalize(surfacePoint - m_Center);
}
