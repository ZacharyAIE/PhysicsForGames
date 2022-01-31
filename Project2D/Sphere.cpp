#include "Sphere.h"
#include "Gizmos.h"

Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour) :
	Rigidbody(SPHERE, position, velocity, 0, mass)
{
	m_radius = radius;
	m_colour = colour;
}

void Sphere::draw()
{
	aie::Gizmos::add2DCircle(m_position, m_radius + .5f, 32, m_colour + glm::vec4(2, 1, 1, 255));
	aie::Gizmos::add2DCircle(m_position, m_radius, 32, m_colour);
	aie::Gizmos::add2DCircle(m_position, m_radius -1, 32, glm::vec4(0,0,0,255));
	
}
