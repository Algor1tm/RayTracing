#pragma once

#include "Ray.h"
#include "AABB.h"

#include <vector>
#include <memory>



class GameObject
{
public:
	virtual bool Intersect(const Ray& ray, HitRecord& record) const = 0;
	virtual bool ConstructAABB(float time0, float time1, AABB& outputBox) const = 0;
};


class GameObjectList: public GameObject
{
public:
	using iterator = std::vector<std::shared_ptr<GameObject>>::iterator;
	using const_iterator = std::vector<std::shared_ptr<GameObject>>::const_iterator;

public:
	GameObjectList() = default;

	bool Intersect(const Ray& ray, HitRecord& record) const override;
	bool ConstructAABB(float time0, float time1, AABB& outputBox) const override;

	void Add(const std::shared_ptr<GameObject>& object) { m_Objects.push_back(object); }

	constexpr const std::vector<std::shared_ptr<GameObject>>& Native() const { return m_Objects; }
	constexpr const auto& Data() const { return m_Objects.data(); }
	constexpr size_t Size() const { return m_Objects.size(); }

	constexpr const auto& operator[](size_t idx) const { return m_Objects[idx]; }
	constexpr auto& operator[](size_t idx) { return m_Objects[idx]; }

	constexpr const_iterator begin() const { return m_Objects.begin(); }
	constexpr const_iterator end() const { return m_Objects.end(); }
	constexpr iterator begin() { return m_Objects.begin(); }
	constexpr iterator end() { return m_Objects.end(); }

private:
	std::vector<std::shared_ptr<GameObject>> m_Objects;
};
