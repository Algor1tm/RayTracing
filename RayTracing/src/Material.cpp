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
		
	rayRef.Direction = record.Normal + Random::InUnitSphere();;

	if (IsNearZero(rayRef.Direction))
		rayRef.Direction = record.Normal;

	(*attenuation) = m_Albedo;
	return true;
}


Metal::Metal(const glm::vec3& color, float fuzziness)
	: m_Albedo(color), m_Fuzziness(glm::clamp(fuzziness, 0.f, 1.f))
{
	
}

bool Metal::Scatter(const HitRecord& record, Ray* ray, glm::vec3* attenuation)
{
	Ray& rayRef = *ray;
	rayRef.Origin = record.Point;

	rayRef.Direction = glm::reflect(rayRef.Direction, record.Normal);
	if(m_Fuzziness != 0)
		rayRef.Direction += m_Fuzziness * Random::InUnitSphere();

	(*attenuation) = m_Albedo;
	return glm::dot(rayRef.Direction, record.Normal) > 0;
}


Dielectric::Dielectric(float refractionIndex)
	: m_RefractionIndex(refractionIndex)
{

}

bool Dielectric::Scatter(const HitRecord& record, Ray* ray, glm::vec3* attenuation)
{
	Ray& rayRef = *ray;
	rayRef.Origin = record.Point;

	float refraction_ratio = record.Inside ? m_RefractionIndex : 1.f / m_RefractionIndex;

	glm::vec3 unitDir = glm::normalize(rayRef.Direction);
	float cos_theta = glm::min(glm::dot(-unitDir, record.Normal), 1.f);
	float sin_theta = glm::sqrt(1.f - cos_theta * cos_theta);

	bool cannot_refract = refraction_ratio * sin_theta > 1.0;
	if (cannot_refract || Reflectance(cos_theta, refraction_ratio) > Random::Float())
		rayRef.Direction = glm::reflect(rayRef.Direction, record.Normal);
	else
		rayRef.Direction = glm::refract(rayRef.Direction, record.Normal, refraction_ratio);

	(*attenuation) = glm::vec3(1.f);
	return true;
}

float Dielectric::Reflectance(float cosine, float refIndex)
{
	float r0 = (1 - refIndex) / (1 + refIndex);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}
