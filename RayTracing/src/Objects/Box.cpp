#include "Box.h"


Box::Box(const glm::vec3& min, const glm::vec3& max, const std::shared_ptr<Material>& material)
	: m_MinPoint(min), m_MaxPoint(max)
{
    m_Sides.Add(std::make_shared<RectXY>(min.x, max.x, min.y, max.y, max.z, material));
    m_Sides.Add(std::make_shared<RectXY>(min.x, max.x, min.y, max.y, min.z, material));

    m_Sides.Add(std::make_shared<RectXZ>(min.x, max.x, min.z, max.z, max.y, material));
    m_Sides.Add(std::make_shared<RectXZ>(min.x, max.x, min.z, max.z, min.y, material));

    m_Sides.Add(std::make_shared<RectYZ>(min.y, max.y, min.z, max.z, max.x, material));
    m_Sides.Add(std::make_shared<RectYZ>(min.y, max.y, min.z, max.z, min.x, material));
}

bool Box::Intersect(const Ray& ray, float minLength, float maxLength, HitRecord& record) const
{
    return m_Sides.Intersect(ray, minLength, maxLength, record);
}

bool Box::ConstructAABB(float time0, float time1, AABB& outputBox) const
{
    outputBox = AABB(m_MinPoint, m_MaxPoint);
    return true;
}
