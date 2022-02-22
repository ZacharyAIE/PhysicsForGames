#pragma once
#include "glm/glm.hpp"

enum ShapeType {
	JOINT = -1,
	PLANE = 0,
	SPHERE,
	BOX,
	SHAPE_COUNT
};

class PhysicsObject
{
protected:
	PhysicsObject(ShapeType a_shapeID) : m_shapeID(a_shapeID) {}

public:
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) = 0;
	virtual void draw() = 0;
	virtual void resetPosition() {};

	virtual float getEnergy() { return 0; }
	float getElasticity() { return m_elasticity; }
	ShapeType getShapeID() { return m_shapeID; }

protected:
	float m_elasticity = 1;
	ShapeType m_shapeID;
	glm::vec4 m_colour;
};

