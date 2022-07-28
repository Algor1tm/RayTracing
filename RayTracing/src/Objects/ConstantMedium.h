#pragma once

#include "GameObject.h"
#include "Materials/Material.h"


class ConstantMedium : public GameObject
{
public:
	ConstantMedium(const std::shared_ptr<GameObject>& boundaries, float density, const glm::vec3& color);
	ConstantMedium(const std::shared_ptr<GameObject>& boundaries, float density, const std::shared_ptr<Texture>& texture);

	bool Intersect(const Ray& ray, float minLength, float maxLength, HitRecord& record) const override;
	bool ConstructAABB(float time0, float time1, AABB& outputBox) const override;

private:
	std::shared_ptr<GameObject> m_Boundaries;
	std::shared_ptr<Material> m_PhaseFunction;
	float m_NegInvDensity;
};
