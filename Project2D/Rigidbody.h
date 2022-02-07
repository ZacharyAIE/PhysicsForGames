#pragma once
#include "PhysicsObject.h"
#include <iostream>

class Rigidbody : public PhysicsObject
{
public:
    Rigidbody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float orientation, float mass, float m_elasticity);
    ~Rigidbody();

    virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
    void applyForce(glm::vec2 force, glm::vec2 pos);

    glm::vec2 getPosition() const { return m_position; }
    glm::vec2 getVelocity() const { return m_velocity; }

    float getOrientatation() { return m_orientation; }
    float getMoment() { return m_moment; }
    float getMass() { return m_mass; }
    float getKineticEnergy();
    float getElasticity() { return m_elasticity; }
    float getAngularVelocity() { return m_angularVelocity; }
    
    void resolveCollision(Rigidbody* actor2, glm::vec2 contact, glm::vec2* collisionNormal = nullptr);

protected:
    glm::vec2 m_position;
    glm::vec2 m_velocity;

    float m_mass;
    float m_orientation; //2D so we only need a single float to represent our orientation 
    float m_angularVelocity;
    float m_moment;
    float m_elasticity = 1;
};

