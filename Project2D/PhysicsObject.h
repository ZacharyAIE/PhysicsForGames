#pragma once
#include "glm/glm.hpp"

/// <summary>
/// This enum determines what type of shape the physics object is.
/// </summary>
enum ShapeType {
	JOINT = -1,
	PLANE = 0,
	SPHERE,
	BOX,
	SHAPE_COUNT
};

/// <summary>
/// The base class for an object in the physics simulation. This contains the energy, elasticity and shape type of the object.
/// </summary>
class PhysicsObject
{
protected:
	PhysicsObject(ShapeType a_shapeID) : m_shapeID(a_shapeID) {}

public:
	/// <summary>
	/// Virtual function that is called everytime update is called in the physics scene. This is to be overidden by physics object child classes.
	/// </summary>
	/// <param name="gravity"></param>
	/// <param name="timeStep"></param>
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) = 0;
	/// <summary>
	/// Virtual function that is called everytime update is called in the physics scene. This is to be overidden by physics object child classes.
	/// </summary>
	virtual void draw() = 0;

	virtual void resetPosition() {};

	virtual float getEnergy() { return 0; }
	float getElasticity() { return m_elasticity; }

	/// <summary>
	/// Returns the shape type of an object.
	/// </summary>
	/// <returns></returns>
	ShapeType getShapeID() { return m_shapeID; }

protected:
	float m_elasticity = 1;
	ShapeType m_shapeID;
	glm::vec4 m_colour;
};

