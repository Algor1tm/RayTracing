#include <glm/glm.hpp>


struct Ray
{
public:
	Ray(const glm::vec3& direction, const glm::vec3& origin = glm::vec3(0))
		: Direction(direction), Origin(origin) {}

	inline glm::vec3 GetPoint(float distance) const
	{
		return Origin + Direction * distance;
	}

public:
	glm::vec3 Direction;
	glm::vec3 Origin;
};

struct DirectionalLight
{
public:
	DirectionalLight(const glm::vec3& direction, const glm::vec3& color = glm::vec3(1))
		: Direction(direction), Color(color) {}

	inline glm::vec3 GetColor(const glm::vec3& normal)
	{
		return Color * glm::dot(-normal, Direction);
	}

public:
	glm::vec3 Direction;
	glm::vec3 Color;
};


class GameObject
{
public:
	virtual bool GetIntersectionPoint(const Ray& ray, glm::vec3& outPoint) const = 0;
	virtual glm::vec3 GetNormal(const glm::vec3& surfacePoint) const = 0;
};


class Sphere : public GameObject
{
public:
	Sphere(float radius, const glm::vec3& center = glm::vec3(0));

	bool GetIntersectionPoint(const Ray& ray, glm::vec3& outPoint) const override;
	glm::vec3 GetNormal(const glm::vec3& surfacePoint) const override;

	const glm::vec3& GetCenter() const { return m_Center; }
	void SetCenter(const glm::vec3& newCenter) { m_Center = newCenter; }

private:
	float m_Radius;
	glm::vec3 m_Center;
};
