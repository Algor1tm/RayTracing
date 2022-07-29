#include "ConstantMedium.h"

#include "Random.h"


ConstantMedium::ConstantMedium(const std::shared_ptr<GameObject>& boundaries, float density, const glm::vec3& color)
	: m_Boundaries(boundaries), m_NegInvDensity(-1.f / density), m_PhaseFunction(std::make_shared<Isotropic>(color))
{

}

ConstantMedium::ConstantMedium(const std::shared_ptr<GameObject>& boundaries, float density, const std::shared_ptr<Texture>& material)
	: m_Boundaries(boundaries), m_NegInvDensity(-1.f / density), m_PhaseFunction(std::make_shared<Isotropic>(material))
{

}

bool ConstantMedium::Intersect(const Ray& ray, float minLength, float maxLength, HitRecord& record) const
{
	HitRecord rec1, rec2;

	if (!m_Boundaries->Intersect(ray, -Infinity(), Infinity(), rec1))
		return false;

	if (!m_Boundaries->Intersect(ray, rec1.Distance + 0.0001f, Infinity(), rec2))
		return false;

	if (rec1.Distance < minLength) rec1.Distance = minLength;
	if (rec2.Distance > maxLength) rec2.Distance = maxLength;

	if (rec1.Distance >= rec2.Distance)
		return false;

	if (rec1.Distance < 0)
		rec1.Distance = 0;

	float rayLength = glm::length(ray.Direction);
	float distanceInsideBoundary = (rec2.Distance - rec1.Distance) * rayLength;
	float hitDistance = m_NegInvDensity * glm::log(Random::Float());

	if (hitDistance > distanceInsideBoundary)
		return false;

	record.Distance = rec1.Distance + hitDistance / rayLength;
	record.Point = ray.At(record.Distance);

	record.Normal = glm::vec3(1.f, 0.f, 0.f);
	record.Inside = false;
	record.ObjectMaterial = m_PhaseFunction;

	return true;
}

bool ConstantMedium::ConstructAABB(float time0, float time1, AABB& outputBox) const
{
	return m_Boundaries->ConstructAABB(time0, time1, outputBox);
}
