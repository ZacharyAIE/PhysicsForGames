#include "PhysicsScene.h"
#include "Sphere.h"
#include "Plane.h"
#include "Box.h"
#include "Spring.h"

glm::vec2 PhysicsScene::m_gravity(0, 0);

PhysicsScene::PhysicsScene() : m_timeStep(0.01f)
{
}

PhysicsScene::~PhysicsScene()
{
	for (auto pActor : m_actors)
	{
		delete pActor;
	}
}

void PhysicsScene::addActor(PhysicsObject* actor)
{
	// Just push an actor to the end of the list
	m_actors.push_back(actor);
}

void PhysicsScene::removeActor(PhysicsObject* actor)
{
	// Search for and erase given actor
	auto it = std::find(m_actors.begin(), m_actors.end(), actor);

	if (it != m_actors.end()) {
		m_actors.erase(it);
	}
}

void PhysicsScene::update(float dt)
{
	// update physics at a fixed time step 

	static float accumulatedTime = 0.0f;
	accumulatedTime += dt;

	while (accumulatedTime >= m_timeStep)
	{
		for (auto pActor : m_actors)
		{
			pActor->fixedUpdate(m_gravity, m_timeStep);
		}

		accumulatedTime -= m_timeStep;

		checkForCollision();
		
		std::cout << getTotalEnergy() << std::endl;
	}
	 
}

void PhysicsScene::draw()
{
	for (auto pActor : m_actors) {
		pActor->draw();
	}
}

float PhysicsScene::getTotalEnergy()
{
	float total = 0;
	for (auto it = m_actors.begin(); it != m_actors.end(); it++)
	{
		PhysicsObject* obj = *it;
		total += obj->getEnergy();
	}
	return total;
}

bool PhysicsScene::sphere2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Sphere* sphere = dynamic_cast<Sphere*>(obj1);
	Plane* plane = dynamic_cast<Plane*>(obj2);

	

	//if we are successful then test for collision 
	if (sphere != nullptr && plane != nullptr)
	{
		glm::vec2 collisionNormal = plane->getNormal();
		float sphereToPlane = glm::dot(sphere->getPosition(), plane->getNormal()) -
			plane->getDistance();

		float intersection = sphere->getRadius() - sphereToPlane;
		float velocityOutOfPlane
			= glm::dot(sphere->getVelocity(), plane->getNormal());

		glm::vec2 contact = sphere->getPosition() + (collisionNormal * -sphere->getRadius());

		if (intersection > 0 && velocityOutOfPlane < 0)
		{
			//set sphere velocity to zero here 
			plane->resolveCollision(sphere, contact);
			return true;
		}
	}
	return false;
}

bool PhysicsScene::plane2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return sphere2Plane(obj2, obj1);
}

bool PhysicsScene::sphere2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	// try to cast objects to sphere and sphere 
	Sphere* sphere1 = dynamic_cast<Sphere*>(obj1);
	Sphere* sphere2 = dynamic_cast<Sphere*>(obj2);

	// if we are successful then test for collision 
	if (sphere1 != nullptr && sphere2 != nullptr)
	{
		float penetration = sphere1->getRadius() + sphere2->getRadius() - glm::distance(sphere1->getPosition(), sphere2->getPosition());
		if (penetration > 0)
		{
			sphere1->resolveCollision(sphere2, (sphere1->getPosition() + sphere2->getPosition()) * 0.5f, nullptr, penetration);

			return true;
		}
	}
		return false;

}

bool PhysicsScene::plane2Box(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Plane* plane = dynamic_cast<Plane*>(obj1);
	Box* box = dynamic_cast<Box*>(obj2);

	//if we are successful then test for collision 
	if (box != nullptr && plane != nullptr)
	{
		int numContacts = 0;
		glm::vec2 contact(0, 0);
		float contactV = 0;

		// get a representative point on the plane 
		glm::vec2 planeOrigin = plane->getNormal() * plane->getDistance();

		// check all four corners to see if we've hit the plane 
		for (float x = -box->getExtents().x; x < box->getWidth(); x += box -> getWidth())
		{
			for (float y = -box->getExtents().y; y < box->getHeight(); y += box -> getHeight())
			{
				// get the position of the corner in world space 
				glm::vec2 p = box->getPosition() + x * box->getLocalX() + y * box -> getLocalY();
				float distFromPlane = glm::dot(p - planeOrigin, plane->getNormal());

				// this is the total velocity of the point in world space 
				glm::vec2 displacement = x * box->getLocalX() + y * box->getLocalY();
				glm::vec2 pointVelocity = box->getVelocity() + box -> getAngularVelocity() * glm::vec2(-displacement.y, displacement.x);
				// and this is the component of the point velocity into the plane 
				float velocityIntoPlane = glm::dot(pointVelocity, plane->getNormal());

				// and moving further in, we need to resolve the collision 
				if (distFromPlane < 0 && velocityIntoPlane <= 0)
				{
					numContacts++;
					contact += p;
					contactV += velocityIntoPlane;
				}
			}
		}

		// we've had a hit - typically only two corners can contact 
		if (numContacts > 0)
		{
			plane->resolveCollision(box, contact / (float)numContacts);
			return true;
		}
	}

	return false;
}

bool PhysicsScene::box2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return plane2Box(obj2, obj1);
}

bool PhysicsScene::box2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Box* box = dynamic_cast<Box*>(obj1);
	Sphere* sphere = dynamic_cast<Sphere*>(obj2);

	if (box != nullptr && sphere != nullptr)
	{
		// transform the circle into the box's coordinate space 
		glm::vec2 circlePosWorld = sphere->getPosition() - box->getPosition();
		glm::vec2 circlePosBox = glm::vec2(glm::dot(circlePosWorld, box -> getLocalX()), glm::dot(circlePosWorld, box->getLocalY()));

		// find the closest point to the circle centre on the box by clamping the coordinates in box - space to the box's extents 
			glm::vec2 closestPointOnBoxBox = circlePosBox;
		glm::vec2 extents = box->getExtents();

		if (closestPointOnBoxBox.x < -extents.x) closestPointOnBoxBox.x = -
			extents.x;
		if (closestPointOnBoxBox.x > extents.x) closestPointOnBoxBox.x = extents.x;
		if (closestPointOnBoxBox.y < -extents.y) closestPointOnBoxBox.y = -
			extents.y;
		if (closestPointOnBoxBox.y > extents.y) closestPointOnBoxBox.y = extents.y;

		// and convert back into world coordinates 
		glm::vec2 closestPointOnBoxWorld = box->getPosition() + closestPointOnBoxBox.x *
			box->getLocalX() + closestPointOnBoxBox.y * box->getLocalY();
		glm::vec2 circleToBox = sphere->getPosition() - closestPointOnBoxWorld;

		float penetration = sphere->getRadius() - glm::length(circleToBox);

		if (penetration > 0)	
		{
			glm::vec2 direction = glm::normalize(circleToBox);
			glm::vec2 contact = closestPointOnBoxWorld;
			box->resolveCollision(sphere, contact, &direction, penetration);
		}
	}

	return false;
}

bool PhysicsScene::sphere2Box(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return box2Sphere(obj2, obj1);
}

bool PhysicsScene::box2Box(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Box* box1 = dynamic_cast<Box*>(obj1);
	Box* box2 = dynamic_cast<Box*>(obj2);
	if (box1 != nullptr && box2 != nullptr) {
		glm::vec2 boxPos = box2->getPosition() - box1->getPosition();
		glm::vec2 norm(0, 0);
		glm::vec2 contact(0, 0);
		float pen = 0;
		int numContacts = 0;
		box1->checkBoxCorners(*box2, contact, numContacts, pen, norm);
		if (box2->checkBoxCorners(*box1, contact, numContacts, pen, norm)) {
			norm = -norm;
		}
		if (pen > 0) {
			box1->resolveCollision(box2, contact / float(numContacts), &norm, pen);
		}
		return true;
	}
	return false;
}

void PhysicsScene::ApplyContactForces(Rigidbody* body1, Rigidbody* body2, glm::vec2 norm, float pen)
{
	float body2Mass = body2 ? body2->getMass() : INT_MAX;
	float body1Factor = body2Mass / (body1->getMass() + body2Mass);
	body1->setPosition(body1->getPosition() - body1Factor * norm * pen);
	if (body2)
		body2->setPosition(body2->getPosition() + (1 - body1Factor) * norm * pen);

}


// function pointer array for doing our collisions 
typedef bool(*fn)(PhysicsObject*, PhysicsObject*); 
 
static fn collisionFunctionArray[] =
{
 PhysicsScene::plane2Plane,  PhysicsScene::plane2Sphere, PhysicsScene::plane2Box,
 PhysicsScene::sphere2Plane, PhysicsScene::sphere2Sphere,  PhysicsScene::sphere2Box,
 PhysicsScene::box2Plane, PhysicsScene::box2Sphere, PhysicsScene::box2Box
}; 
 
void PhysicsScene::checkForCollision() 
{ 
 int actorCount = m_actors.size(); 
 
 //need to check for collisions against all objects except this one. 
 for (int outer = 0; outer < actorCount - 1; outer++) 
 { 
  for (int inner = outer + 1; inner < actorCount; inner++) 
  { 
   PhysicsObject* object1 = m_actors[outer]; 
   PhysicsObject* object2 = m_actors[inner]; 
   int shapeId1 = object1->getShapeID(); 
   int shapeId2 = object2->getShapeID(); 

   if (shapeId1 < 0 || shapeId2 < 0)
	   continue;
 
   // using function pointers 
   int functionIdx = (shapeId1 * SHAPE_COUNT) + shapeId2; 
   fn collisionFunctionPtr = collisionFunctionArray[functionIdx]; 
   if (collisionFunctionPtr != nullptr) 
   { 
    // did a collision occur? 
    collisionFunctionPtr(object1, object2);   
   } 
  } 
 } 
} 
