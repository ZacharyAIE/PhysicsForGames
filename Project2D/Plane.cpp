#include "Plane.h"
#include "PhysicsScene.h"

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

void Plane::resolveCollision(Rigidbody* actor2, glm::vec2 contact)
{
	// the position at which we'll apply the force relative to the object's COM 
	glm::vec2 localContact = contact - actor2->getPosition();

	// the plane isn't moving, so the relative velocity is just actor2's velocity at the contact point
		glm::vec2 vRel = actor2->getVelocity() + actor2->getAngularVelocity() * glm::vec2(-localContact.y, localContact.x);
	float velocityIntoPlane = glm::dot(vRel, m_normal);

	// Average Elasticity of the plane and rigidbody
	float e = (getElasticity() + actor2->getElasticity()) / 2;

	// this is the perpendicular distance we apply the force at relative to the COM, so Torque = F * r
	float r = glm::dot(localContact, glm::vec2(m_normal.y, -m_normal.x));

	// work out the "effective mass" - this is a combination of moment of 
	// inertia and mass, and tells us how much the contact point velocity  
	// will change with the force we're applying 
	float mass0 = 1.0f / (1.0f / actor2->getMass() + (r * r) / actor2 -> getMoment());

	float j = -(1 + e) * velocityIntoPlane * mass0;

	glm::vec2 force = m_normal * j;

	float kePre = actor2->getKineticEnergy();

	actor2->applyForce(force, contact - actor2->getPosition());

	float pen = glm::dot(contact, m_normal) - m_distanceToOrigin;
	PhysicsScene::ApplyContactForces(actor2, nullptr, m_normal, pen);

	float kePost = actor2->getKineticEnergy();

	float deltaKE = kePost - kePre;
	if (deltaKE > kePost * 0.01f)
		std::cout << "Kinetic Energy discrepancy greater than 1% detected!!";
}

