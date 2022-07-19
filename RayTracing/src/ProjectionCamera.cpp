#include "ProjectionCamera.h"


ProjectionCamera::ProjectionCamera(const CameraOrientation& orientation, const CameraProps& props)
	: m_Position(orientation.Position), m_Properties(props)
{
	float viewportHeight = 2.f * glm::tan(m_Properties.FOV / 2);
	float viewportWidth = viewportHeight * m_Properties.AspectRatio;

	glm::vec3 lookVec = glm::normalize(m_Position - orientation.LookAt);
	m_HorizontalVec = glm::normalize(glm::cross(orientation.Up, lookVec));
	glm::vec3 verticalVec = glm::cross(lookVec, m_HorizontalVec);

	m_Horizontal = m_HorizontalVec * m_Properties.FocusDist * viewportWidth;
	m_Vertical = verticalVec * m_Properties.FocusDist * viewportHeight;
	m_LowerLeftCorner = m_Position - m_Horizontal / 2.f - m_Vertical / 2.f - m_Properties.FocusDist * lookVec;
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

	m_Horizontal = m_HorizontalVec * m_Properties.FocusDist * viewportWidth;

	m_LowerLeftCorner -= m_Horizontal / 2.f;
}
