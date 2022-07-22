#include "Environment.h"

#include <glm/glm.hpp>


struct CameraOrientation
{
	glm::vec3 Position;
	glm::vec3 LookAt;
	glm::vec3 Up;
};

struct CameraProps
{
	float FOV;
	float AspectRatio;
	float FocusDist;
	float LensRadius;
};


class ProjectionCamera
{
public:
	ProjectionCamera(const CameraOrientation& orientation, const CameraProps& props);

	Ray CastRay(glm::vec2 uv);
	void OnResize(float aspectRatio);

private:
	glm::vec3 m_Position;
	CameraProps m_Properties;

	glm::vec3 m_HorizontalDir;
	glm::vec3 m_Horizontal;
	glm::vec3 m_Vertical;
	glm::vec3 m_VerticalDir;
	glm::vec3 m_LowerLeftCorner;
};