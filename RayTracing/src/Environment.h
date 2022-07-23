#pragma once

#include <glm/glm.hpp>

#include <memory>
#include <vector>

// defines in Material.h
class Material;


struct Ray
{
public:
	Ray(const glm::vec3& direction, const glm::vec3& origin = glm::vec3(0))
		: Direction(direction), Origin(origin) {}

	inline glm::vec3 At(float distance) const
	{
		return Origin + Direction * distance;
	}

public:
	glm::vec3 Direction;
	glm::vec3 Origin;

public:
	static constexpr float MinLength = 0.001f;
	static constexpr float MaxLength = 1000.f;
};


struct HitRecord
{
	glm::vec3 Point;
	glm::vec3 Normal;
	bool Inside;
	std::shared_ptr<Material> ObjectMaterial;
};

class GameObject
{
public:
	virtual bool Intersect(const Ray& ray, float* distance) const = 0;
	virtual glm::vec3 GetNormal(const glm::vec3& surfacePoint) const = 0;
	virtual const std::shared_ptr<Material>& GetMaterial() const = 0;
};


class Sphere : public GameObject
{
public:
	Sphere(const glm::vec3& center, float radius, const std::shared_ptr<Material>& material);

	bool Intersect(const Ray& ray, float* distance) const override;
	glm::vec3 GetNormal(const glm::vec3& surfacePoint) const override;

	const std::shared_ptr<Material>& GetMaterial() const override { return m_Material; }

	const glm::vec3& GetCenter() const { return m_Center; }
	void SetCenter(const glm::vec3& newCenter) { m_Center = newCenter; }

private:
	float m_Radius;
	glm::vec3 m_Center;
	std::shared_ptr<Material> m_Material;
};


class GameObjectList
{
public:
	using iterator = std::vector<std::shared_ptr<GameObject>>::iterator;
	using const_iterator = std::vector<std::shared_ptr<GameObject>>::const_iterator;

public:
	GameObjectList() = default;

	bool ShootRay(const Ray& ray, HitRecord* record);

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
