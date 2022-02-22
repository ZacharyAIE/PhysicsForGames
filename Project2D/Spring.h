#pragma once
#include "PhysicsObject.h"
#include "Rigidbody.h"

class Spring :
    public PhysicsObject
{
public:
    Spring(Rigidbody* body1, Rigidbody* body2, float damping, float springCoefficient, float restLength = 0, 
        glm::vec2 contact1 = glm::vec2(0, 0), glm::vec2 contact2 = glm::vec2(0, 0));

    virtual void fixedUpdate(glm::vec2 gravity, float timeStep);

    virtual void draw();

    glm::vec2 getContact1();
    glm::vec2 getContact2();

protected:
    Rigidbody* m_body1;
    Rigidbody* m_body2;

    glm::vec2 m_contact1;
    glm::vec2 m_contact2;

    float m_damping;
    float m_restLength = 5;
    float m_springCoefficient; // the restoring force
};

