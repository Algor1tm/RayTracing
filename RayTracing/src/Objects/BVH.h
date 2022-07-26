#pragma once

#include "GameObject.h"
#include "AABB.h"


class BVHNode: public GameObject
{
public:
	BVHNode() = default;
	BVHNode(const GameObjectList& objects, float time0, float time1);
	BVHNode(const std::vector<std::shared_ptr<GameObject>>& objects, size_t start, size_t end, float time0, float time1);

	bool Intersect(const Ray& ray, float minLength, float maxLength, HitRecord& record) const override;
	bool ConstructAABB(float time0, float time1, AABB& outputBox) const override;

private:
	std::shared_ptr<GameObject> m_Left;
	std::shared_ptr<GameObject> m_Right;
	AABB m_Box;
};

