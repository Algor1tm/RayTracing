#include "BVH.h"
#include "Random.h"

#include <algorithm>


// Axis: 0 - x, 1 - y, 2 - z
static inline bool BoxCompare(const std::shared_ptr<GameObject>& left, const std::shared_ptr<GameObject>& right, int axis)
{
	ASSERT(axis < 3 && axis > -1, "Bad arguments\n");

	AABB boxRight, boxLeft;

	if (!left->ConstructAABB(0, 0, boxLeft) || !right->ConstructAABB(0, 0, boxRight))
		ASSERT(false, "No bounding box in BVHNode constructor\n");

	return boxLeft.Min()[axis] < boxRight.Min()[axis];
}

static inline bool BoxCompareX(const std::shared_ptr<GameObject>& left, const std::shared_ptr<GameObject>& right)
{
	return BoxCompare(left, right, 0);
}

static inline bool BoxCompareY(const std::shared_ptr<GameObject>& left, const std::shared_ptr<GameObject>& right)
{
	return BoxCompare(left, right, 1);
}

static inline bool BoxCompareZ(const std::shared_ptr<GameObject>& left, const std::shared_ptr<GameObject>& right)
{
	return BoxCompare(left, right, 2);
}



BVHNode::BVHNode(const GameObjectList& objects, float time0, float time1)
	: BVHNode(objects.Native(), 0, objects.Size(), time0, time1)
{

}

BVHNode::BVHNode(const std::vector<std::shared_ptr<GameObject>>& objects, size_t start, size_t end, float time0, float time1)
{
	uint8_t axis = Random::Int(0, 2);
	auto comparator =
		(axis == 0) ? BoxCompareX
		: (axis == 1) ? BoxCompareY
		: BoxCompareZ;

	size_t objectsCount = end - start;
	if (objectsCount == 1)
	{
		m_Left = m_Right = objects[start];
		return;
	}
	else if (objectsCount == 2)
	{
		if (comparator(objects[start], objects[start + 1]))
		{
			m_Left = objects[start];
			m_Right = objects[start + 1];
		}
		else
		{
			m_Left = objects[start + 1];
			m_Right = objects[start];
		}
	}
	else
	{
		auto tmpObjects = objects;

		std::sort(tmpObjects.begin() + start, tmpObjects.end() + end, comparator);

		size_t mid = start + objectsCount / 2;
		m_Left = std::make_shared<BVHNode>(tmpObjects, start, mid, time0, time1);
		m_Right = std::make_shared<BVHNode>(tmpObjects, mid, end, time0, time1);
	}

	AABB boxLeft, boxRight;
	if (!m_Left->ConstructAABB(time0, time1, boxLeft) || m_Right->ConstructAABB(time0, time1, boxRight))
		ASSERT(false, "No bounding box in bvh_node constructor\n");

	m_Box = boxLeft.Merge(boxRight);
}

bool BVHNode::Intersect(const Ray& ray, HitRecord& record) const 
{
	if (!m_Box.Intersect(ray))
		return false;

	bool left = m_Left->Intersect(ray, record);

	return left ? true : m_Right->Intersect(ray, record);
}

bool BVHNode::ConstructAABB(float time0, float time1, AABB& outputBox) const
{
	outputBox = m_Box;
	return true;
}
