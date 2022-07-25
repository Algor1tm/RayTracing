#include "ProjectionCamera.h"
#include "Random.h"


ProjectionCamera::ProjectionCamera()
	: ProjectionCamera(
		CameraOrientation({ 0.f, 0.f, 0.f }, { 0.f, 0.f, 1.f }, { 0.f, 1.f, 0.f }),
		CameraProps({glm::radians(45.f), 16.f / 9.f, 1.f, 0.f}))
{

}

ProjectionCamera::ProjectionCamera(const CameraOrientation& orientation, const CameraProps& props, float time0, float time1)
	: m_Position(orientation.Position), m_Properties(props), m_Time0(time0), m_Time1(time1)
{
	float viewportHeight = 2.f * glm::tan(m_Properties.FOV / 2);
	float viewportWidth = viewportHeight * m_Properties.AspectRatio;

	glm::vec3 lookDir = glm::normalize(m_Position - orientation.LookAt);
	m_HorizontalDir = glm::normalize(glm::cross(orientation.Up, lookDir));
	m_VerticalDir = glm::cross(lookDir, m_HorizontalDir);

	m_Horizontal = m_Properties.FocusDist * viewportWidth * m_HorizontalDir;
	m_Vertical = m_Properties.FocusDist * viewportHeight * m_VerticalDir;
	m_LowerLeftCorner = m_Position - m_Horizontal / 2.f - m_Vertical / 2.f - m_Properties.FocusDist * lookDir;
}

Ray ProjectionCamera::CastRay(glm::vec2 uv)
{
	glm::vec3 offset;
	if (m_Properties.LensRadius != 0)
	{
		glm::vec3 rd = m_Properties.LensRadius * Random::InUnitDisk();
		offset = m_HorizontalDir * rd.x + m_VerticalDir * rd.y;
	}
	else
	{
		offset = glm::vec3(0.f);
	}

	return Ray(
		m_LowerLeftCorner + uv.x * m_Horizontal + uv.y * m_Vertical - m_Position - offset, 
		m_Position + offset,
		Random::Float(m_Time0, m_Time1));
}

void ProjectionCamera::OnResize(float aspectRatio)
{
	m_Properties.AspectRatio = aspectRatio;

	float viewportHeight = 2.f * glm::tan(m_Properties.FOV / 2);
	float viewportWidth = viewportHeight * m_Properties.AspectRatio;

	m_LowerLeftCorner += m_Horizontal / 2.f;

	m_Horizontal = m_Properties.FocusDist * viewportWidth * m_HorizontalDir;

	m_LowerLeftCorner -= m_Horizontal / 2.f;
}
