#pragma once

#include "GameObject.h"


class RectXY: public GameObject
{
public:
	RectXY(float x0, float x1, float y0, float y1, float z, const std::shared_ptr<Material>& material);

	bool Intersect(const Ray& ray, float minLength, float maxLength, HitRecord& record) const override;
	bool ConstructAABB(float time0, float time1, AABB& outputBox) const override;

private:
	std::shared_ptr<Material> m_Material;
	float m_x0, m_x1;
	float m_y0, m_y1;
	float m_z;
};


class RectXZ : public GameObject
{
public:
	RectXZ(float x0, float x1, float z0, float z1, float y, const std::shared_ptr<Material>& material);

	bool Intersect(const Ray& ray, float minLength, float maxLength, HitRecord& record) const override;
	bool ConstructAABB(float time0, float time1, AABB& outputBox) const override;

private:
	std::shared_ptr<Material> m_Material;
	float m_x0, m_x1;
	float m_z0, m_z1;
	float m_y;
};


class RectYZ : public GameObject
{
public:
	RectYZ(float y0, float y1, float z0, float z1, float x, const std::shared_ptr<Material>& material);

	bool Intersect(const Ray& ray, float minLength, float maxLength, HitRecord& record) const override;
	bool ConstructAABB(float time0, float time1, AABB& outputBox) const override;

private:
	std::shared_ptr<Material> m_Material;
	float m_y0, m_y1;
	float m_z0, m_z1;
	float m_x;
};
