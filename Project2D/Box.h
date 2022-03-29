#pragma once
#include "Rigidbody.h"
#include "Gizmos.h"


/// <summary>
/// This class is responible for storing the information needed for the simulation of a box object. A Rigidbody shape with 4 sides and 2 extents.
/// </summary>
class Box :
    public Rigidbody
{
public:
    Box(glm::vec2 extents, glm::vec2 position, glm::vec2 velocity, float orientation, float mass, float elasticity, float linearDrag, float angularDrag, glm::vec4 colour);

    virtual void draw();
    /// <summary>
    /// Getter function for the box dimensions.
    /// </summary>
    /// <returns> Returns a vector 2 of the distance the edges are from the box's centre.</returns>
    glm::vec2 getExtents() const { return m_extents; }
    /// <summary>
    /// 
    /// </summary>
    /// <returns>Returns a vector 2 that determines the colour of the box</returns>
    glm::vec2 getColour() { return m_colour; }

    /// <summary>
    /// 
    /// </summary>
    /// <returns>Returns the X extents of the box squared</returns>
    float getWidth() const { return getExtents().x * 2; }
    /// <summary>
    /// 
    /// </summary>
    /// <returns>Returns the Y extents of the box squared</returns>
    float getHeight() const { return getExtents().y * 2; }

    bool checkBoxCorners(const Box& box, glm::vec2& contact, int& numContacts, float& pen, glm::vec2& edgeNormal);

protected:
    glm::vec2 m_extents;   // the halfedge lengths  
    glm::vec4 m_colour;

    
};

