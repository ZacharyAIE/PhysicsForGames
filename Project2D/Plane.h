#pragma once
#include "Gizmos.h"
#include "Rigidbody.h"

class Plane :
    public PhysicsObject
{
public:
    Plane(glm::vec2 normal, float distance);
    ~Plane();

    virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
    virtual void draw();
    virtual void resetPosition();

    void resolveCollision(Rigidbody* actor2, glm::vec2 contact);

    glm::vec2 getNormal() { return m_normal; }
    float getDistance() { return m_distanceToOrigin; }

protected:
    glm::vec2 m_normal;
    glm::vec4 m_colour = glm::vec4(1, 1, 1, 1);
    float m_distanceToOrigin;
};

