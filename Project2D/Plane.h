#pragma once
#include "Gizmos.h"
#include "Rigidbody.h"

/// <summary>
/// An infinite plane in the given axis, with infinite depth. This object is static and cannot move.
/// </summary>
class Plane :
    public PhysicsObject
{
public:
    Plane(glm::vec2 normal, float distance);
    ~Plane();

    virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
    virtual void draw();
    virtual void resetPosition();

    /// <summary>
    /// Handles collisions with objects.
    /// </summary>
    /// <param name="actor2"></param>
    /// <param name="contact"></param>
    void resolveCollision(Rigidbody* actor2, glm::vec2 contact);

    /// <summary>
    /// 
    /// </summary>
    /// <returns>Returns the normal direction as a vec2</returns>
    glm::vec2 getNormal() { return m_normal; }
    /// <summary>
    /// 
    /// </summary>
    /// <returns>Returns the offset of the plane in relation to the centre of the physics scene.</returns>
    float getDistance() { return m_distanceToOrigin; }

protected:
    glm::vec2 m_normal;
    glm::vec4 m_colour = glm::vec4(1, 1, 1, 1);
    float m_distanceToOrigin;
};

