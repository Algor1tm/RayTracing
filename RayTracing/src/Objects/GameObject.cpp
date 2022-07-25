#include "GameObject.h"


bool GameObjectList::ShootRay(const Ray& ray, HitRecord& record)
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
