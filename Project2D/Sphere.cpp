#include "Sphere.h"


Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, float elasticity, glm::vec4 colour) :
	Rigidbody(SPHERE, position, velocity, 0, mass, elasticity)
{
	m_radius = radius;
	m_colour = colour;
}

void Sphere::draw()
{
	glm::vec2 end = glm::vec2(std::cos(m_orientation), std::sin(m_orientation)) *
		m_radius;

	aie::Gizmos::add2DCircle(m_position, m_radius, 32, m_colour);
	aie::Gizmos::add2DCircle(m_position, m_radius -1, 32, glm::vec4(0,0,0,255));
	aie::Gizmos::add2DLine(m_position, m_position + end, glm::vec4(1, 1, 1, 1));
	
}
