#include "Instances.h"
#include "Utils.h"



Translate::Translate(const std::shared_ptr<GameObject>& object, const glm::vec3& offset)
	: m_Object(object), m_Offset(offset)
{

}

bool Translate::Intersect(const Ray& ray, float minLength, float maxLength, HitRecord& record) const
{
	Ray translated = Ray(ray.Direction, ray.Origin - m_Offset, ray.Time);
	if (!m_Object->Intersect(translated, minLength, maxLength, record))
		return false;

	record.Point += m_Offset;
	record.SetFaceNormal(translated);
	return true;
}

bool Translate::ConstructAABB(float time0, float time1, AABB& outputBox) const
{
	if (!m_Object->ConstructAABB(time0, time1, outputBox))
		return false;

	outputBox = AABB(outputBox.Min() + m_Offset, outputBox.Max() + m_Offset);
	return true;
}


RotateY::RotateY(const std::shared_ptr<GameObject>& object, float rotation)
    : m_Object(object)
{
    m_Sin = sin(rotation);
    m_Cos = cos(rotation);
    m_HasBox = m_Object->ConstructAABB(0, 1, m_Box);

    glm::vec3 min(Infinity());
    glm::vec3 max(-Infinity());

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                float x = i * m_Box.Max().x + (1 - i) * m_Box.Min().x;
                float y = j * m_Box.Max().y + (1 - j) * m_Box.Min().y;
                float z = k * m_Box.Max().z + (1 - k) * m_Box.Min().z;
                
                float newx = m_Cos * x + m_Sin * z;
                float newz = -m_Sin * x + m_Cos * z;

                glm::vec3 tester(newx, y, newz);

                for (int c = 0; c < 3; c++) {
                    min[c] = glm::min(min[c], tester[c]);
                    max[c] = glm::max(max[c], tester[c]);
                }
            }
        }
    }

    m_Box = AABB(min, max);
}

bool RotateY::Intersect(const Ray& ray, float minLength, float maxLength, HitRecord& record) const
{
    glm::vec3 origin = ray.Origin;
    glm::vec3 direction = ray.Direction;

    origin.x = m_Cos * ray.Origin.x - m_Sin * ray.Origin.z;
    origin.z = m_Sin * ray.Origin.x + m_Cos * ray.Origin.z;

    direction.x = m_Cos * ray.Direction.x - m_Sin * ray.Direction.z;
    direction.z = m_Sin * ray.Direction.x + m_Cos * ray.Direction.z;

    Ray rotated = Ray(direction, origin, ray.Time);
    if (!m_Object->Intersect(rotated, minLength, maxLength, record))
        return false;

    glm::vec3 point = record.Point;
    glm::vec3 normal = record.Normal;

    point.x = m_Cos * record.Point.x + m_Sin * record.Point.z;
    point.z = -m_Sin * record.Point.x + m_Cos * record.Point.z;

    normal.x = m_Cos * record.Normal.x + m_Sin * record.Normal.z;
    normal.z = -m_Sin * record.Normal.x + m_Cos * record.Normal.z;

    record.Point = point;
    record.Normal = normal;
    record.SetFaceNormal(rotated);

    return true;
}

bool RotateY::ConstructAABB(float time0, float time1, AABB& outputBox) const
{
    outputBox = m_Box;
    return m_HasBox;
}


RotateX::RotateX(const std::shared_ptr<GameObject>& object, float rotation)
    : m_Object(object)
{
    m_Sin = sin(rotation);
    m_Cos = cos(rotation);
    m_HasBox = m_Object->ConstructAABB(0, 1, m_Box);

    glm::vec3 min(Infinity());
    glm::vec3 max(-Infinity());

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                float x = i * m_Box.Max().x + (1 - i) * m_Box.Min().x;
                float y = j * m_Box.Max().y + (1 - j) * m_Box.Min().y;
                float z = k * m_Box.Max().z + (1 - k) * m_Box.Min().z;

                float newy = m_Cos * y + m_Sin * z;
                float newz = -m_Sin * y + m_Cos * z;

                glm::vec3 tester(x, newy, newz);

                for (int c = 0; c < 3; c++) {
                    min[c] = glm::min(min[c], tester[c]);
                    max[c] = glm::max(max[c], tester[c]);
                }
            }
        }
    }

    m_Box = AABB(min, max);
}

bool RotateX::Intersect(const Ray& ray, float minLength, float maxLength, HitRecord& record) const
{
    glm::vec3 origin = ray.Origin;
    glm::vec3 direction = ray.Direction;

    origin.y = m_Cos * ray.Origin.y - m_Sin * ray.Origin.z;
    origin.z = m_Sin * ray.Origin.y + m_Cos * ray.Origin.z;

    direction.y = m_Cos * ray.Direction.y - m_Sin * ray.Direction.z;
    direction.z = m_Sin * ray.Direction.y + m_Cos * ray.Direction.z;

    Ray rotated = Ray(direction, origin, ray.Time);
    if (!m_Object->Intersect(rotated, minLength, maxLength, record))
        return false;

    glm::vec3 point = record.Point;
    glm::vec3 normal = record.Normal;

    point.y = m_Cos * record.Point.y + m_Sin * record.Point.z;
    point.z = -m_Sin * record.Point.y + m_Cos * record.Point.z;

    normal.y = m_Cos * record.Normal.y + m_Sin * record.Normal.z;
    normal.z = -m_Sin * record.Normal.y + m_Cos * record.Normal.z;

    record.Point = point;
    record.Normal = normal;
    record.SetFaceNormal(rotated);

    return true;
}

bool RotateX::ConstructAABB(float time0, float time1, AABB& outputBox) const
{
    outputBox = m_Box;
    return m_HasBox;
}
