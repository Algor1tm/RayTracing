#pragma once

#include "GameObject.h"
#include "Material.h"


class Sphere : public GameObject
{
public:
	Sphere(const glm::vec3& center, float radius, const std::shared_ptr<Material>& material);

	bool Intersect(const Ray& ray, float minLength, float maxLength, HitRecord& record) const override;
	bool ConstructAABB(float time0, float time1, AABB& outputBox) const override;

private:
	glm::vec3 m_Center;
	float m_Radius;

	std::shared_ptr<Material> m_Material;
};


class MovingSphere : public GameObject
{
public:
	MovingSphere(const glm::vec3& center0, float time0, const glm::vec3& center1, 
		float time1, float radius, const std::shared_ptr<Material>& material);

	bool Intersect(const Ray& ray, float minLength, float maxLength, HitRecord& record) const override;
	bool ConstructAABB(float time0, float time1, AABB& outputBox) const override;

private:
	glm::vec3 GetCenter(float time) const;

private:
	glm::vec3 m_Center0;
	float m_Time0;
	glm::vec3 m_Center1;
	float m_Time1;
	float m_Radius;

	std::shared_ptr<Material> m_Material;
};
