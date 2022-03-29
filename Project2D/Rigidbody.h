#pragma once
#include "PhysicsObject.h"
#include <iostream>

#define MIN_LINEAR_THRESHOLD 0.01f
#define MIN_ANGULAR_THRESHOLD 0.01f
/// <summary>
/// This class is responsible for most of the physical characteristics that are common between all Pigidbody objects in the simulation.
/// </summary>
class Rigidbody : public PhysicsObject
{
public:
    Rigidbody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float orientation, float mass, float m_elasticity, float linearDrag, float angularDrag);
    ~Rigidbody(){}

    virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
    /// <summary>
    /// Applies a force to the rigidbody
    /// </summary>
    /// <param name="force">The force to apply to the object as a vec2</param>
    /// <param name="pos">Position to apply the force to. For angular velocity.</param>
    void applyForce(glm::vec2 force, glm::vec2 pos);

    /// <summary>
    /// Manually sets the position of the rigidbody.
    /// </summary>
    /// <param name="position">The position to move the rigidbody to.</param>
    void setPosition(glm::vec2 position);
    /// <summary>
    /// Sets the rigidbody to Kinematic or non-Kinematic based on the parameter.
    /// </summary>
    /// <param name="state"></param>
    void setKinematic(bool state) { m_isKinematic = state; }

    /// <summary>
    /// 
    /// </summary>
    /// <returns>Returns the position of the object as a vec2</returns>
    glm::vec2 getPosition() const { return m_position; }
    /// <summary>
    /// 
    /// </summary>
    /// <returns>Returns the velocity as a vec2</returns>
    glm::vec2 getVelocity() const { return m_velocity; }

    /// <summary>
    /// 
    /// </summary>
    /// <returns>Returns the orientation of the object as a float</returns>
    float getOrientatation() { return m_orientation; }
    /// <summary>
    /// 
    /// </summary>
    /// <returns>Returns the momentum of the object as a float or returns the maximum integer value if the object is kinematic.</returns>
    float getMoment() { return m_isKinematic ? INT_MAX : m_moment; }
    /// <summary>
    /// 
    /// </summary>
    /// <returns>Returns the mass of the object as a float or returns the maximum integer value if the object is kinematic.</returns>
    float getMass() { return m_isKinematic ? INT_MAX : m_mass; }
    /// <summary>
    /// 
    /// </summary>
    /// <returns>Returns the sum of kinetic and potential of the object as a float.</returns>
    virtual float getEnergy() { return getKineticEnergy() + getPotentialEnergy(); }
    /// <summary>
    /// 
    /// </summary>
    /// <returns>Returns the kinetic energy of the object.</returns>
    float getKineticEnergy();
    /// <summary>
    /// Returns the potential energy of the object as a float.
    /// </summary>
    /// <returns></returns>
    float getPotentialEnergy();
    /// <summary>
    /// 
    /// </summary>
    /// <returns>Returns the angular velocity or rotation speed of the object as a float.</returns>
    float getAngularVelocity() { return m_angularVelocity; }

    /// <summary>
    /// Translates the local position of the object to world space.
    /// </summary>
    /// <param name="pos"></param>
    /// <returns>Returns the world space coordinates of the object as a vec2</returns>
    glm::vec2 toWorld(glm::vec2 pos);

    /// <summary>
    /// Returns the local X position of the object as a vec2.
    /// </summary>
    /// <returns></returns>
    glm::vec2 getLocalX() { return m_localX; }

    /// <summary>
    /// Returns the local Y position of the object as a vec2.
    /// </summary>
    /// <returns></returns>
    glm::vec2 getLocalY() { return m_localY; }

    /// <summary>
    /// Normalises the orientation of the object to prevent issues.
    /// </summary>
    void updateAxes();

    /// <summary>
    /// 
    /// </summary>
    /// <returns>Returns the kinematic state of the object as a boolean</returns>
    bool isKinematic() { return m_isKinematic; }
    
    /// <summary>
    /// Handles collisions with other objects.
    /// </summary>
    /// <param name="actor2"></param>
    /// <param name="contact"></param>
    /// <param name="collisionNormal"></param>
    /// <param name="pen"></param>
    void resolveCollision(Rigidbody* actor2, glm::vec2 contact, glm::vec2* collisionNormal, float pen);

protected:
    glm::vec2 m_position;
    glm::vec2 m_velocity;
    float m_mass;
    float m_orientation; //2D so we only need a single float to represent our orientation 
    float m_angularVelocity;
    float m_moment;
    float m_linearDrag;
    float m_angularDrag;
    bool m_isKinematic = false;

    glm::vec2 m_localX;
    glm::vec2 m_localY;
};

