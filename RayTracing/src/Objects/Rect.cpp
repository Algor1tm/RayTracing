#include "Rect.h"


RectXY::RectXY(float x0, float x1, float y0, float y1, float z, const std::shared_ptr<Material>& material)
	: m_x0(x0), m_x1(x1), m_y0(y0), m_y1(y1), m_z(z), m_Material(material)
{

}

bool RectXY::Intersect(const Ray& ray, float minLength, float maxLength, HitRecord& record) const
{
	float dist = (m_z - ray.Origin.z) / ray.Direction.z;
	if (dist < minLength || dist > maxLength)
		return false;

	float rayAtX = ray.Origin.x + ray.Direction.x * dist;
	float rayAtY = ray.Origin.y + ray.Direction.y * dist;
	if (rayAtX < m_x0 || rayAtX > m_x1 || rayAtY < m_y0 || rayAtY > m_y1)
		return false;

	record.Distance = dist;
	record.Point = glm::vec3(rayAtX, rayAtY, m_z);
	record.Normal = glm::vec3(0, 0, 1);
	record.SetFaceNormal(ray);

	record.ObjectMaterial = m_Material;
	record.TexCoords = glm::vec2((rayAtX - m_x0) / (m_x1 - m_x0), (rayAtY - m_y0) / (m_y1 - m_y0));

	return true;
}

bool RectXY::ConstructAABB(float time0, float time1, AABB& outputBox) const
{
	// The bounding box must have non - zero width in each dimension, so pad the Z
	// dimension a small amount
	outputBox = AABB(glm::vec3(m_x0, m_y0, m_z - 0.0001f), glm::vec3(m_x1, m_y1, m_z + 0.0001f));
	return true;
}


RectXZ::RectXZ(float x0, float x1, float z0, float z1, float y, const std::shared_ptr<Material>& material)
	: m_x0(x0), m_x1(x1), m_z0(z0), m_z1(z1), m_y(y), m_Material(material)
{

}

bool RectXZ::Intersect(const Ray& ray, float minLength, float maxLength, HitRecord& record) const
{
	float dist = (m_y - ray.Origin.y) / ray.Direction.y;
	if (dist < minLength || dist > maxLength)
		return false;

	float rayAtX = ray.Origin.x + ray.Direction.x * dist;
	float rayAtZ = ray.Origin.z + ray.Direction.z * dist;
	if (rayAtX < m_x0 || rayAtX > m_x1 || rayAtZ < m_z0 || rayAtZ > m_z1)
		return false;

	record.Distance = dist;
	record.Point = glm::vec3(rayAtX, m_y, rayAtZ);
	record.Normal = glm::vec3(0, 0, 1);
	record.SetFaceNormal(ray);

	record.ObjectMaterial = m_Material;
	record.TexCoords = glm::vec2((rayAtX - m_x0) / (m_x1 - m_x0), (rayAtZ - m_z0) / (m_z1 - m_z0));

	return true;
}

bool RectXZ::ConstructAABB(float time0, float time1, AABB& outputBox) const
{
	outputBox = AABB(glm::vec3(m_x0, m_y - 0.0001f, m_z0), glm::vec3(m_x1, m_y + 0.0001f, m_z1));
	return true;
}


RectYZ::RectYZ(float y0, float y1, float z0, float z1, float x, const std::shared_ptr<Material>& material)
	: m_y0(y0), m_y1(y1), m_z0(z0), m_z1(z1), m_x(x), m_Material(material)
{

}

bool RectYZ::Intersect(const Ray& ray, float minLength, float maxLength, HitRecord& record) const
{
	float dist = (m_x - ray.Origin.x) / ray.Direction.x;
	if (dist < minLength || dist > maxLength)
		return false;

	float rayAtY = ray.Origin.y + ray.Direction.y * dist;
	float rayAtZ = ray.Origin.z + ray.Direction.z * dist;
	if (rayAtY < m_y0 || rayAtY > m_y1 || rayAtZ < m_z0 || rayAtZ > m_z1)
		return false;

	record.Distance = dist;
	record.Point = glm::vec3(m_x, rayAtY, rayAtZ);
	record.Normal = glm::vec3(0, 0, 1);
	record.SetFaceNormal(ray);

	record.ObjectMaterial = m_Material;
	record.TexCoords = glm::vec2((rayAtY - m_y0) / (m_y1 - m_y0), (rayAtZ - m_z0) / (m_z1 - m_z0));

	return true;
}

bool RectYZ::ConstructAABB(float time0, float time1, AABB& outputBox) const
{
	outputBox = AABB(glm::vec3(m_x - 0.0001f, m_y0, m_z0), glm::vec3(m_x + 0.0001f, m_y1, m_z1));
	return true;
}
