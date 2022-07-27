#include "Material.h"
#include "Random.h"


Lambertian::Lambertian(const glm::vec3& color)
	: m_Albedo(std::make_shared<SolidColor>(color)) {}

Lambertian::Lambertian(const std::shared_ptr<Texture>& texture)
	: m_Albedo(texture) {}

bool Lambertian::Scatter(const HitRecord& record, Ray& ray, glm::vec3& attenuation) const
{
	ray.Origin = record.Point;
		
	ray.Direction = record.Normal + Random::InUnitSphere();;

	if (IsNearZero(ray.Direction))
		ray.Direction = record.Normal;

	attenuation = m_Albedo->Value(record.TexCoords, record.Point);
	return true;
}


Metal::Metal(const glm::vec3& color, float fuzziness)
	: m_Albedo(color), m_Fuzziness(glm::clamp(fuzziness, 0.f, 1.f))
{
	
}

bool Metal::Scatter(const HitRecord& record, Ray& ray, glm::vec3& attenuation) const
{
	ray.Origin = record.Point;

	ray.Direction = glm::reflect(ray.Direction, record.Normal);
	if(m_Fuzziness != 0)
		ray.Direction += m_Fuzziness * Random::InUnitSphere();

	attenuation = m_Albedo;
	return glm::dot(ray.Direction, record.Normal) > 0;
}


Dielectric::Dielectric(float refractionIndex)
	: m_RefractionIndex(refractionIndex) {}

bool Dielectric::Scatter(const HitRecord& record, Ray& ray, glm::vec3& attenuation) const
{
	constexpr glm::vec3 white(1.f);

	ray.Origin = record.Point;

	float refraction_ratio = record.Inside ? m_RefractionIndex : 1.f / m_RefractionIndex;

	glm::vec3 unitDir = glm::normalize(ray.Direction);
	float cos_theta = -glm::dot(unitDir, record.Normal);
	float sin_theta = glm::sqrt(1.f - cos_theta * cos_theta);

	bool cannot_refract = refraction_ratio * sin_theta > 1.f;
	if (cannot_refract || Reflectance(cos_theta, refraction_ratio) > Random::Float())
		ray.Direction = glm::reflect(unitDir, record.Normal);
	else
		ray.Direction = glm::refract(unitDir, record.Normal, refraction_ratio);

	attenuation = white;
	return true;
}

float Dielectric::Reflectance(float cosine, float refIndex) const
{
	float r0 = (1 - refIndex) / (1 + refIndex);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}


DiffuseLight::DiffuseLight(const glm::vec3& color)
	: DiffuseLight(std::make_shared<SolidColor>(color)) {}

DiffuseLight::DiffuseLight(const std::shared_ptr<Texture>& texture)
	: m_Emit(texture) {}

glm::vec3 DiffuseLight::Emitted(glm::vec2 texCoords, const glm::vec3& point) const
{
	return m_Emit->Value(texCoords, point);
}

bool DiffuseLight::Scatter(const HitRecord& record, Ray& ray, glm::vec3& attenuation) const
{
	return false;
}
