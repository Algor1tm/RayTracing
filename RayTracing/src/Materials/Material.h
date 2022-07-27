#pragma once

#include "Objects/Ray.h"
#include "Texture.h"


class Material
{
public:
	virtual glm::vec3 Emitted(glm::vec2 texCoords, const glm::vec3& point) const { return glm::vec3(0.f); };
	virtual bool Scatter(const HitRecord& record, Ray& ray, glm::vec3& attenuation) const = 0;
};


class Lambertian: public Material
{
public:
	Lambertian(const glm::vec3& color);
	Lambertian(const std::shared_ptr<Texture>& texture);

	bool Scatter(const HitRecord& record, Ray& ray, glm::vec3& attenuation) const override;

private:
	std::shared_ptr<Texture> m_Albedo;
};


class Metal : public Material
{
public:
	Metal(const glm::vec3& color, float fuzziness = 0);

	bool Scatter(const HitRecord& record, Ray& ray, glm::vec3& attenuation) const override;

private:
	glm::vec3 m_Albedo;
	float m_Fuzziness;
};


class Dielectric: public Material
{
public:
	Dielectric(float refractionIndex);

	bool Scatter(const HitRecord& record, Ray& ray, glm::vec3& attenuation) const override;

private:
	float Reflectance(float cosine, float refIndex) const;

private:
	float m_RefractionIndex;
};


class DiffuseLight: public Material
{
public:
	DiffuseLight(const glm::vec3& color);
	DiffuseLight(const std::shared_ptr<Texture>& texture);

	glm::vec3 Emitted(glm::vec2 texCoords, const glm::vec3& point) const override;
	bool Scatter(const HitRecord& record, Ray& ray, glm::vec3& attenuation) const override;

private:
	std::shared_ptr<Texture> m_Emit;
};
