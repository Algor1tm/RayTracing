#include "GameObject.h"


bool GameObjectList::Intersect(const Ray& ray, HitRecord& record) const
{
	HitRecord tmpRecord = record;
	record.Distance = Ray::MaxLength;
	bool hitAnything = false;

	for (size_t i = 0; i < m_Objects.size(); ++i)
	{
		if (m_Objects[i]->Intersect(ray, tmpRecord))
		{
			hitAnything = true;
			if (tmpRecord.Distance < record.Distance)
				record = tmpRecord;
		}
	}

	return hitAnything;
}

bool GameObjectList::ConstructAABB(float time0, float time1, AABB& outputBox) const
{
	AABB result;
	bool firstBox = true;

	for (const auto& object : m_Objects)
	{
		if (!object->ConstructAABB(time0, time1, result))
			return false;

		firstBox ? outputBox = result : outputBox.Merge(result);
		firstBox = false;
	}

	return true;
}
