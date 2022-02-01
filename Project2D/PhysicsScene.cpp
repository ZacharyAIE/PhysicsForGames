#include "PhysicsScene.h"

PhysicsScene::PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0, 0))
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
		
	}
}

void PhysicsScene::draw()
{
	for (auto pActor : m_actors) {
		pActor->draw();
	}
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
		if (intersection > 0 && velocityOutOfPlane < 0)
		{
			//set sphere velocity to zero here 
			sphere->applyForce(-sphere->getVelocity() * sphere->getMass());
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
		if (glm::distance(sphere1->getPosition(), sphere2->getPosition()) <= sphere1->getRadius() + sphere2->getRadius()) {
			//Do Stuff
			/*sphere1->applyForce(-sphere1->getVelocity());
			sphere2->applyForce(-sphere2->getVelocity());*/
			sphere2->resolveCollision(sphere1);
			
		}
		return true;
	}
		return false;

}

// function pointer array for doing our collisions 
typedef bool(*fn)(PhysicsObject*, PhysicsObject*); 
 
static fn collisionFunctionArray[] = 
{ 
 PhysicsScene::plane2Plane,  PhysicsScene::plane2Sphere, 
 PhysicsScene::sphere2Plane, PhysicsScene::sphere2Sphere,  
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
