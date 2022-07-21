#include "Environment.h"


class Material
{
public:
	virtual bool Scatter(const HitRecord& record, Ray* ray, glm::vec3* attenuation) = 0;
};


class Lambertian : public Material
{
public:
	Lambertian(const glm::vec3& color);

	bool Scatter(const HitRecord& record, Ray* ray, glm::vec3* attenuation) override;

private:
	glm::vec3 m_Albedo;
};