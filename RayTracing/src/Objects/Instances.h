#pragma once 

#include "GameObject.h"


class Translate : public GameObject
{
public:
	Translate(const std::shared_ptr<GameObject>& object, const glm::vec3& offset);

	bool Intersect(const Ray& ray, float minLength, float maxLength, HitRecord& record) const override;
	bool ConstructAABB(float time0, float time1, AABB& outputBox) const override;

private:
	std::shared_ptr<GameObject> m_Object;
	glm::vec3 m_Offset;
};


class RotateY : public GameObject
{
public:
	RotateY(const std::shared_ptr<GameObject>& object, float rotation);

	bool Intersect(const Ray& ray, float minLength, float maxLength, HitRecord& record) const override;
	bool ConstructAABB(float time0, float time1, AABB& outputBox) const override;

private:
	std::shared_ptr<GameObject> m_Object;
	float m_Sin, m_Cos;
	AABB m_Box;
	bool m_HasBox;
};
