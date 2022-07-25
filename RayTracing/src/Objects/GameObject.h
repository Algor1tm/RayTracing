#pragma once

#include "Ray.h"

#include <vector>
#include <memory>


class GameObject
{
public:
	virtual bool Intersect(const Ray& ray, HitRecord& record) const = 0;
};


class GameObjectList
{
public:
	using iterator = std::vector<std::shared_ptr<GameObject>>::iterator;
	using const_iterator = std::vector<std::shared_ptr<GameObject>>::const_iterator;

public:
	GameObjectList() = default;

	bool ShootRay(const Ray& ray, HitRecord& record);

	std::shared_ptr<GameObject> operator[](size_t idx) const { return m_Objects[idx]; }
	std::shared_ptr<GameObject>& operator[](size_t idx) { return m_Objects[idx]; }

	const_iterator begin() const { return m_Objects.begin(); }
	const_iterator end() const { return m_Objects.end(); }
	iterator begin() { return m_Objects.begin(); }
	iterator end() { return m_Objects.end(); }

	void Add(const std::shared_ptr<GameObject>& object) { m_Objects.push_back(object); }

private:
	std::vector<std::shared_ptr<GameObject>> m_Objects;
};
