#pragma once
#include "Rigidbody.h"
#include "Gizmos.h"
#include <glm/vec4.hpp>

class Sphere :
    public Rigidbody
{
public:
    Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, float elasticity, float linearDrag, float angularDrag, glm::vec4 colour );
    ~Sphere();

    virtual void draw();

    float getRadius() { return m_radius; }
    glm::vec4 getColour() { return m_colour; }

protected:
    float m_radius;
    glm::vec4 m_colour;
};