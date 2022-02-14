#pragma once
#include "Rigidbody.h"
#include "Gizmos.h"

class Box :
    public Rigidbody
{
public:
    Box(glm::vec2 extents, glm::vec2 position, glm::vec2 velocity, float orientation, float mass, float elasticity, float linearDrag, float angularDrag, glm::vec4 colour);

    virtual void draw();

    glm::vec2 getExtents() const { return m_extents; }
    glm::vec2 getColour() { return m_colour; }

    float getWidth() const { return getExtents().x * 2; }
    float getHeight() const { return getExtents().y * 2; }

    bool checkBoxCorners(const Box& box, glm::vec2& contact, int& numContacts, float& pen, glm::vec2& edgeNormal);

protected:
    glm::vec2 m_extents;   // the halfedge lengths  
    glm::vec4 m_colour;

    
};

