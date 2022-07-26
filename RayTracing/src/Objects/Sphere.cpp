#include "Sphere.h"

#include <glm/gtc/constants.hpp>


Sphere::Sphere(const glm::vec3& center, float radius, const std::shared_ptr<Material>& material)
	: m_Radius(radius), m_Center(center), m_Material(material)
{

}

bool Sphere::Intersect(const Ray& ray, float minLength, float maxLength, HitRecord& record) const
{
	// (bx^2 + by^2 + bz^2)t^2 + 2(b * (a - O))t + (a - O)^2 - r^2) = 0
	// a - ray origin
	// b - ray direction
	// t - hit distance
	// O - shere centre
	// r - sphere radius

	glm::vec3 originCenter = ray.Origin - m_Center;

	// ax^2 + bx + c = 0
	float a = glm::dot(ray.Direction, ray.Direction);
	float half_b = glm::dot(ray.Direction, originCenter);
	float c = glm::dot(originCenter, originCenter) - m_Radius * m_Radius;

	float D = half_b * half_b - a * c;

	if (D < 0)
		return false;

	float sqrtD = glm::sqrt(D);

	float root = (-half_b - sqrtD) / a;
	if (root <= minLength || root >= maxLength)
	{
		root = (-half_b + sqrtD) / a;
		if (root <= minLength || root >= maxLength)
			return false;
	}

	record.Distance = root;
	record.Point = ray.At(root);
	record.Normal = (record.Point - m_Center) / m_Radius;
	record.SetFaceNormal(ray);

	record.ObjectMaterial = m_Material;
	record.TexCoords = GetTexCoords(record.Point);

	return true;
}

bool Sphere::ConstructAABB(float time0, float time1, AABB& outputBox) const
{
	outputBox = AABB(m_Center - glm::vec3(m_Radius), m_Center + glm::vec3(m_Radius));
	return true;
}

glm::vec2 Sphere::GetTexCoords(const glm::vec3& point) 
{
	float theta = glm::atan(-point.y);
	float phi = glm::atan(-point.z, point.x) + glm::pi<float>();

	return glm::vec2(phi / 2 * glm::pi<float>(), theta / glm::pi<float>());
}


MovingSphere::MovingSphere(const glm::vec3& center0, float time0, const glm::vec3& center1,
	float time1, float radius, const std::shared_ptr<Material>& material)
	: m_Center0(center0), m_Time0(time0), m_Center1(center1), m_Time1(time1), m_Radius(radius), m_Material(material)
{

}

bool MovingSphere::Intersect(const Ray& ray, float minLength, float maxLength, HitRecord& record) const
{
	glm::vec3 originCenter = ray.Origin - GetCenter(ray.Time);

	float a = glm::dot(ray.Direction, ray.Direction);
	float half_b = glm::dot(ray.Direction, originCenter);
	float c = glm::dot(originCenter, originCenter) - m_Radius * m_Radius;

	float D = half_b * half_b - a * c;

	if (D < 0)
		return false;

	float sqrtD = glm::sqrt(D);

	float root = (-half_b - sqrtD) / a;
	if (root <= minLength || root >= maxLength)
	{
		root = (-half_b + sqrtD) / a;
		if (root <= minLength || root >= maxLength)
			return false;
	}

	record.Distance = root;
	record.Point = ray.At(root);
	record.Normal = (record.Point - GetCenter(ray.Time)) / m_Radius;
	record.ObjectMaterial = m_Material;

	record.SetFaceNormal(ray);

	return true;
}

bool MovingSphere::ConstructAABB(float time0, float time1, AABB& outputBox) const
{
	AABB box0 = AABB(GetCenter(time0) - glm::vec3(m_Radius), GetCenter(time0) + glm::vec3(m_Radius));
	AABB box1 = AABB(GetCenter(time1) - glm::vec3(m_Radius), GetCenter(time1) + glm::vec3(m_Radius));

	outputBox = box0.Merge(box1);

	return true;
}

glm::vec3 MovingSphere::GetCenter(float time) const
{
	return m_Center0 + ((time - m_Time0) / (m_Time1 - m_Time0)) * (m_Center1 - m_Center0);
}
