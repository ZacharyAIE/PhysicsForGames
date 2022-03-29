#pragma once
#include "glm/vec2.hpp"
#include "glm/geometric.hpp"
#include <vector>
#include "PhysicsObject.h"

class Rigidbody;

/// <summary>
/// This class contains a list of all physics objects as well as a list of possible collision types.
/// </summary>
class PhysicsScene
{
public:
	PhysicsScene();
	~PhysicsScene();

	/// <summary>
	/// Adds an actor to the physics scene.
	/// </summary>
	/// <param name="actor"></param>
	void addActor(PhysicsObject* actor);
	/// <summary>
	/// Removes an actor from the physics scene.
	/// </summary>
	/// <param name="actor"></param>
	void removeActor(PhysicsObject* actor);
	/// <summary>
	/// Calls fixedUpdate on all PhysicsObjects in the physics scene.
	/// </summary>
	/// <param name="dt"></param>
	void update(float dt);
	/// <summary>
	/// Calls draw on all actors in the physics scene.
	/// </summary>
	void draw();

	/// <summary>
	/// Sets the strength and direction of gravity within the physics scene.
	/// </summary>
	/// <param name="gravity"></param>
	void setGravity(const glm::vec2 gravity) { m_gravity = gravity; }
	/// <summary>
	/// 
	/// </summary>
	/// <returns>Returns the m_gravity variable as a glm::vec2</returns>
	static glm::vec2 getGravity() { return m_gravity; }

	float getTotalEnergy();

	/// <summary>
	/// Sets the physics timestep for the scene. This is the rate at which the physics engine will update all objects.
	/// </summary>
	/// <param name="timeStep"></param>
	void setTimeStep(const float timeStep) { m_timeStep = timeStep; }

	/// <summary>
	/// 
	/// </summary>
	/// <returns>Returns the physics timestep of the scene.</returns>
	float getTimeStep() { return m_timeStep; }

	/// <summary>
	/// Describes a plane to plane collision.
	/// </summary>
	/// <param name="obj1"></param>
	/// <param name="obj2"></param>
	/// <returns></returns>
	static bool plane2Plane(PhysicsObject* obj1, PhysicsObject* obj2) { return false; }

	/// <summary>
	/// Calls sphere2Plane with the parameters reversed.
	/// </summary>
	/// <param name="obj1"></param>
	/// <param name="obj2"></param>
	/// <returns></returns>
	static bool plane2Sphere(PhysicsObject* obj1, PhysicsObject* obj2);

	/// <summary>
	/// Describes a plane to sphere collision.
	/// </summary>
	/// <param name="obj1"></param>
	/// <param name="obj2"></param>
	/// <returns></returns>
	static bool sphere2Plane(PhysicsObject* obj1, PhysicsObject* obj2);

	/// <summary>
	/// Describes a sphere to sphere collision.
	/// </summary>
	/// <param name="obj1"></param>
	/// <param name="obj2"></param>
	/// <returns></returns>
	static bool sphere2Sphere(PhysicsObject* obj1, PhysicsObject* obj2);

	/// <summary>
	/// Describes a plane to box collision.
	/// </summary>
	/// <param name="obj1"></param>
	/// <param name="obj2"></param>
	/// <returns></returns>
	static bool plane2Box(PhysicsObject* obj1, PhysicsObject* obj2);

	/// <summary>
	/// Calls plane2Box with the parameters reversed.
	/// </summary>
	/// <param name="obj1"></param>
	/// <param name="obj2"></param>
	/// <returns></returns>
	static bool box2Plane(PhysicsObject* obj1, PhysicsObject* obj2);

	/// <summary>
	/// Describes a box to sphere collision.
	/// </summary>
	/// <param name="obj1"></param>
	/// <param name="obj2"></param>
	/// <returns></returns>
	static bool box2Sphere(PhysicsObject* obj1, PhysicsObject* obj2);

	/// <summary>
	/// Calls box2Sphere with the parameters reversed.
	/// </summary>
	/// <param name="obj1"></param>
	/// <param name="obj2"></param>
	/// <returns></returns>
	static bool sphere2Box(PhysicsObject* obj1, PhysicsObject* obj2);

	/// <summary>
	/// Describes a box to box collision
	/// </summary>
	/// <param name="obj1"></param>
	/// <param name="obj2"></param>
	/// <returns></returns>
	static bool box2Box(PhysicsObject* obj1, PhysicsObject* obj2);

	/// <summary>
	/// Applies a force between objects to prevent them from entering eachother at any point.
	/// </summary>
	/// <param name="body1"></param>
	/// <param name="body2"></param>
	/// <param name="norm"></param>
	/// <param name="pen"></param>
	static void ApplyContactForces(Rigidbody* body1, Rigidbody* body2, glm::vec2 norm, float pen);
	
	/// <summary>
	/// Selects the correct type of collision function for the collision that occurred.
	/// </summary>
	void checkForCollision();

protected:
	static glm::vec2 m_gravity;
	float m_timeStep;
	std::vector<PhysicsObject*> m_actors;
};