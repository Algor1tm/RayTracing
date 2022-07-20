#include "ProjectionCamera.h"


ProjectionCamera::ProjectionCamera(const CameraOrientation& orientation, const CameraProps& props)
	: m_Position(orientation.Position), m_Properties(props)
{
	float viewportHeight = 2.f * glm::tan(m_Properties.FOV / 2);
	float viewportWidth = viewportHeight * m_Properties.AspectRatio;

	//glm::vec3 lookDir = glm::normalize(m_Position - orientation.LookAt);
	//m_HorizontalDir = glm::normalize(glm::cross(orientation.Up, lookDir));
	//glm::vec3 verticalDir = glm::cross(lookDir, m_HorizontalDir);

	//m_Horizontal = m_HorizontalDir * m_Properties.FocusDist * viewportWidth;
	//m_Vertical = verticalDir * m_Properties.FocusDist * viewportHeight;
	//m_LowerLeftCorner = m_Position - m_Horizontal / 2.f - m_Vertical / 2.f - m_Properties.FocusDist * lookDir;

	m_Horizontal = glm::vec3(viewportWidth, 0, 0);
	m_Vertical = glm::vec3(0, viewportHeight, 0);
	m_LowerLeftCorner = m_Position - m_Horizontal / 2.f - m_Vertical / 2.f - glm::vec3(0, 0, 1.f);
}

Ray ProjectionCamera::CastRay(glm::vec2 uv)
{
	return Ray( m_LowerLeftCorner + uv.x * m_Horizontal + uv.y * m_Vertical - m_Position, m_Position);
}

void ProjectionCamera::OnResize(float aspectRatio)
{
	m_Properties.AspectRatio = aspectRatio;

	float viewportHeight = 2.f * glm::tan(m_Properties.FOV / 2);
	float viewportWidth = viewportHeight * m_Properties.AspectRatio;

	m_LowerLeftCorner += m_Horizontal / 2.f;

	//m_Horizontal = m_HorizontalDir * m_Properties.FocusDist * viewportWidth;
	m_Horizontal = glm::vec3(viewportWidth, 0, 0);

	m_LowerLeftCorner -= m_Horizontal / 2.f;
}
