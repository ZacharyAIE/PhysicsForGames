#include "Plane.h"

Plane::Plane(glm::vec2 normal, float distance) : PhysicsObject(PLANE)
{
	m_distanceToOrigin = distance;
	m_normal = glm::normalize(normal);
}

void Plane::fixedUpdate(glm::vec2 gravity, float timeStep)
{
}

void Plane::draw()
{
	float lineSegmentLength = 300;
	glm::vec2 centerPoint = m_normal * m_distanceToOrigin;
	// easy to rotate normal through 90 degrees around z 
	glm::vec2 parallel(m_normal.y, -m_normal.x);
	glm::vec4 colourFade = m_colour;
	colourFade.a = 0;
	glm::vec2 start = centerPoint + (parallel * lineSegmentLength);
	glm::vec2 end = centerPoint - (parallel * lineSegmentLength);
	//aie::Gizmos::add2DLine(start, end, colour); 
	aie::Gizmos::add2DTri(start, end, start - m_normal * 10.0f, m_colour, m_colour,
		colourFade);
	aie::Gizmos::add2DTri(end, end - m_normal * 10.0f, start - m_normal * 10.0f,
		m_colour, colourFade, colourFade);
}

void Plane::resetPosition()
{
}