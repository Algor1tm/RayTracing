#include "Environment.h"


Sphere::Sphere(float radius, const glm::vec3& center, const std::shared_ptr<Material>& material)
	: m_Radius(radius), m_Center(center), m_Material(material)
{

}

bool Sphere::Intersect(const Ray& ray, float* distance) const
{
	// (bx^2 + by^2 + bz^2)t^2 + 2(b * (a - O))t + (a - O)^2 - r^2) = 0
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

	*distance = root;
	return true;
}

glm::vec3 Sphere::GetNormal(const glm::vec3& surfacePoint) const
{
	return glm::normalize(surfacePoint - m_Center);
}



Plane::Plane(const glm::vec3& normal, const glm::vec3& point, const std::shared_ptr<Material>& material)
	: m_Point(point), m_Material(material)
{
	m_Normal = glm::normalize(normal);
}

bool Plane::Intersect(const Ray& ray, float* distance) const
{
	float dot = glm::dot(ray.Direction, m_Normal);

	if (dot > -0.001f)
		return false;

	float result = glm::dot(m_Normal, (m_Point - ray.Origin)) / dot;
	if (result < Ray::MinLength || result > Ray::MaxLength)
		return false;

	*distance = result;
	return true;
}

glm::vec3 Plane::GetNormal(const glm::vec3& surfacePoint) const
{
	return m_Normal;
}


bool GameObjectList::ShootRay(const Ray& ray, HitRecord* record)
{
	float closestHit = Ray::MaxLength;
	size_t ObjectIdx = -1;
	for (size_t i = 0; i < m_Objects.size(); ++i)
	{
		float distance;
		if (!m_Objects[i]->Intersect(ray, &distance))
			continue;

		if (distance < closestHit)
		{
			ObjectIdx = i;
			closestHit = distance;
		}
	}

	if (ObjectIdx == -1)
		return false;

	HitRecord& rec = *record;

	rec.Point = ray.At(closestHit);
	rec.Normal = m_Objects[ObjectIdx]->GetNormal(rec.Point);

	float normalDotDir = glm::dot(rec.Normal, ray.Direction);
	rec.Inside = normalDotDir > 0;

	rec.ObjectMaterial = m_Objects[ObjectIdx]->GetMaterial();

	return true;
}
