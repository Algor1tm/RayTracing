#include "Material.h"
#include "Random.h"


static bool IsNearZero(const glm::vec3& vec)
{
	static constexpr float EPSILON = 1e-6f;
	return glm::all(glm::lessThan(glm::abs(vec), glm::vec3(EPSILON)));
}


Lambertian::Lambertian(const glm::vec3& color)
	: m_Albedo(color)
{

}

bool Lambertian::Scatter(const HitRecord& record, Ray* ray, glm::vec3* attenuation)
{
	Ray& rayRef = *ray;
	rayRef.Origin = record.Point;
		
	glm::vec3 rand = Random::InUnitSphere();
	rand = glm::dot(rand, record.Normal) > 0 ? rand : -rand;

	rayRef.Direction = record.Normal + rand;

	if (IsNearZero(rayRef.Direction))
		rayRef.Direction = record.Normal;

	(*attenuation) = m_Albedo;

	return true;
}
