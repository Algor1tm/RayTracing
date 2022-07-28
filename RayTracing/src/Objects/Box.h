#pragma once 

#include "GameObject.h"
#include "Rect.h"


class Box : public GameObject
{
public:
	Box(const glm::vec3& min, const glm::vec3& max, const std::shared_ptr<Material>& material);

	bool Intersect(const Ray& ray, float minLength, float maxLength, HitRecord& record) const override;
	bool ConstructAABB(float time0, float time1, AABB& outputBox) const override;

private:
	GameObjectList m_Sides;
	glm::vec3 m_MinPoint, m_MaxPoint;
};
