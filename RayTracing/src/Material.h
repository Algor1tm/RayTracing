#pragma once

#include "Environment.h"


class Material
{
public:
	virtual bool Scatter(const HitRecord& record, Ray* ray, glm::vec3* attenuation) = 0;
};


class Lambertian: public Material
{
public:
	Lambertian(const glm::vec3& color);

	bool Scatter(const HitRecord& record, Ray* ray, glm::vec3* attenuation) override;

private:
	glm::vec3 m_Albedo;
};


class Metal : public Material
{
public:
	Metal(const glm::vec3& color, float fuzziness = 0);

	bool Scatter(const HitRecord& record, Ray* ray, glm::vec3* attenuation) override;

private:
	glm::vec3 m_Albedo;
	float m_Fuzziness;
};


class Dielectric: public Material
{
public:
	Dielectric(float refractionIndex);

	bool Scatter(const HitRecord& record, Ray* ray, glm::vec3* attenuation) override;

private:
	float Reflectance(float cosine, float refIndex);

private:
	float m_RefractionIndex;
};
