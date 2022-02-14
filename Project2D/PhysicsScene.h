#pragma once
#include "glm/vec2.hpp"
#include "glm/geometric.hpp"
#include <vector>
#include "PhysicsObject.h"
#include "Sphere.h"
#include "Plane.h"
#include "Box.h"

class PhysicsScene
{
public:
	PhysicsScene();
	~PhysicsScene();

	void addActor(PhysicsObject* actor);
	void removeActor(PhysicsObject* actor);
	void update(float dt);
	void draw();

	void setGravity(const glm::vec2 gravity) { m_gravity = gravity; }
	static glm::vec2 getGravity() { return m_gravity; }

	float getTotalEnergy();

	void setTimeStep(const float timeStep) { m_timeStep = timeStep; }
	float getTimeStep() { return m_timeStep; }

	static bool plane2Plane(PhysicsObject* obj1, PhysicsObject* obj2) { return false; }
	static bool plane2Sphere(PhysicsObject* obj1, PhysicsObject* obj2);
	static bool sphere2Plane(PhysicsObject* obj1, PhysicsObject* obj2);
	static bool sphere2Sphere(PhysicsObject* obj1, PhysicsObject* obj2);
	static bool plane2Box(PhysicsObject* obj1, PhysicsObject* obj2);
	static bool box2Plane(PhysicsObject* obj1, PhysicsObject* obj2);
	static bool box2Sphere(PhysicsObject* obj1, PhysicsObject* obj2);
	static bool sphere2Box(PhysicsObject* obj1, PhysicsObject* obj2);
	static bool box2Box(PhysicsObject* obj1, PhysicsObject* obj2);

	static void ApplyContactForces(Rigidbody* body1, Rigidbody* body2, glm::vec2 norm, float pen);

	
	

	void checkForCollision();

protected:
	static glm::vec2 m_gravity;
	float m_timeStep;
	std::vector<PhysicsObject*> m_actors;
};