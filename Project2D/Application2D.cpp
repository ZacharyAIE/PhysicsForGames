#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "glm/ext.hpp"
#include "SoftBody.h"
#include "Sphere.h"
#include "Plane.h"
#include "Box.h"
#include "Spring.h"
#include <Gizmos.h>

Application2D::Application2D() {

}

Application2D::~Application2D() {

}

bool Application2D::startup() {
	// increase the 2d line count to maximize the number of objects we can draw 
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();

	m_font = new aie::Font("./font/consolas.ttf", 32);
	
	m_timer = 0;

	m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(glm::vec2(0,-10));
	m_physicsScene->setTimeStep(0.01f);

	SpringTest();
	//SpawnContactForceTest();
	//Rope(2);


	//Spawn Planes
	m_physicsScene->addActor(new Plane(glm::vec2(0, 1), -45));
	m_physicsScene->addActor(new Plane(glm::vec2(1, 0), -80));
	m_physicsScene->addActor(new Plane(glm::vec2(0, -1), -50));
	m_physicsScene->addActor(new Plane(glm::vec2(-1, 0), -80));

	return true;
}

glm::vec2 Application2D::screenToWorld(glm::vec2 screenPos)
{
	glm::vec2 worldPos = screenPos;

	// move the centre of the screen to (0,0) 
	worldPos.x -= getWindowWidth() / 2;
	worldPos.y -= getWindowHeight() / 2;

	// scale according to our extents 
	worldPos.x *= 2.0f * extents / getWindowWidth();
	worldPos.y *= 2.0f * extents / (aspectRatio * getWindowHeight());

	return worldPos;
}

void Application2D::shutdown() {
	
	delete m_font;
	delete m_2dRenderer;
}

void Application2D::update(float deltaTime) {

	m_timer += deltaTime;

	// input example
	aie::Input* input = aie::Input::getInstance();

	// Update the camera position using the arrow keys
	float camPosX;
	float camPosY;
	m_2dRenderer->getCameraPos(camPosX, camPosY);

	// SPAWN SPHERES WHEN LEFT MOUSE BUTTON IS DOWN
	if (input->wasMouseButtonPressed(0)) {
		int xScreen, yScreen;
		input->getMouseXY(&xScreen, &yScreen);
		glm::vec2 worldPos = screenToWorld(glm::vec2(xScreen, yScreen));

		Sphere* sphere = new Sphere(worldPos, glm::vec2(glm::linearRand(-100, 100), glm::linearRand(-100, 100)), 10.0f, 3, 1, 0, 0, glm::vec4(1, 0, 1, 1));
		//sphere->setKinematic(true);
		m_physicsScene->addActor(sphere);
	}

	// SPAWN BOXES WHEN LEFT MOUSE BUTTON IS DOWN
	if (input->wasMouseButtonPressed(1)) {
		int xScreen, yScreen;
		input->getMouseXY(&xScreen, &yScreen);
		glm::vec2 worldPos = screenToWorld(glm::vec2(xScreen, yScreen));
		m_physicsScene->addActor(new Box(glm::vec2(3, 3), worldPos, glm::vec2(glm::linearRand(-100, 100), glm::linearRand(-100, 100)), 45, 10, 1, .3f, .3f, glm::vec4(0, 1, 0, 1)));
	}

	m_2dRenderer->setCameraPos(camPosX, camPosY);

	aie::Gizmos::clear();

	m_physicsScene->update(deltaTime);
	m_physicsScene->draw();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();
	
	// draw your stuff here! 
	aie::Gizmos::draw2D(glm::ortho<float>(-extents, extents, -extents / aspectRatio,
		extents / aspectRatio, -1.0f, 1.0f));

	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 720 - 64);

	// done drawing sprites
	m_2dRenderer->end();
}

void Application2D::SpawnBounceTest()
{
	//Spawn Spheres
	m_physicsScene->addActor(new Sphere(glm::vec2(40, 0), glm::vec2(-30, -30), 10.0f, 3, 1, 0, 0, glm::vec4(1, 0, 1, 1)));
	m_physicsScene->addActor(new Sphere(glm::vec2(20, 0), glm::vec2(-30, -30), 10.0f, 3, 1, 0, 0, glm::vec4(1, 0, 0, 1)));
	m_physicsScene->addActor(new Sphere(glm::vec2(-20, 0), glm::vec2(30, 30), 10.0f, 3, 1, 0, 0, glm::vec4(1, 1, 0, 1)));
	m_physicsScene->addActor(new Sphere(glm::vec2(-40, 0), glm::vec2(30, 30), 10.0f, 3, 1, 0, 0, glm::vec4(0, 1, 0, 1)));

	m_physicsScene->addActor(new Sphere(glm::vec2(0, 40), glm::vec2(-30, -30), 10.0f, 3, 1, 0, 0, glm::vec4(1, 0, 1, 1)));
	m_physicsScene->addActor(new Sphere(glm::vec2(0, 20), glm::vec2(-30, -30), 10.0f, 3, 1, 0, 0, glm::vec4(1, 0, 0, 1)));
	m_physicsScene->addActor(new Sphere(glm::vec2(0, -20), glm::vec2(30, 30), 10.0f, 3, 1, 0, 0, glm::vec4(1, 1, 0, 1)));
	m_physicsScene->addActor(new Sphere(glm::vec2(0, -40), glm::vec2(30, 30), 10.0f, 3, 1, 0, 0, glm::vec4(0, 1, 0, 1)));

	m_physicsScene->addActor(new Box(glm::vec2(3, 3), glm::vec2(0, 0), glm::vec2(0, 0), 45, 10, 1, .3f, .3f, glm::vec4(0, 1, 0, 1)));
	m_physicsScene->addActor(new Box(glm::vec2(3, 3), glm::vec2(0, 8), glm::vec2(0, 0), 45, 10, 1, .3f, .3f, glm::vec4(0, 1, 0, 1)));
}

void Application2D::SpawnContactForceTest()
{
	m_physicsScene->addActor(new Box(glm::vec2(3, 3), glm::vec2(0, 0), glm::vec2(0, 0), 45, 10, 1, .3f, .3f, glm::vec4(0, 1, 0, 1)));
	m_physicsScene->addActor(new Box(glm::vec2(3, 3), glm::vec2(0, 0), glm::vec2(0, 0), 45, 10, 1, .3f, .3f, glm::vec4(1, 0, 0, 1)));
	
}

void Application2D::Rope(int num)
{
	Sphere* prev = nullptr;
	for (int i = 0; i < num; i++)
	{
		// spawn a sphere to the right and below the previous one, so that the whole rope acts under   swings
			Sphere* sphere = new Sphere(glm::vec2(i * 5, 30 - i * 10), glm::vec2(0), 10, 3, 1, 0, 0, glm::vec4(0, 1, 0, 1));
		if (i == 0)
			sphere->setKinematic(true);
		m_physicsScene->addActor(sphere);
		if (prev)
			m_physicsScene->addActor(new Spring(sphere, prev, 7, 500));
		prev = sphere;
	}
	// add a kinematic box at an angle for the rope to drape over
	Box* box = new Box(glm::vec2(0, -20), glm::vec2(0), glm::vec2(8, 2), 45, 10, 1, .3f, .3f, glm::vec4(1, 0, 0, 1));
	box->setKinematic(true);
	m_physicsScene->addActor(box);
}

void Application2D::SpringTest()
{
	std::vector<std::string> sb;
	sb.push_back("000000");
	sb.push_back("000000");
	sb.push_back("00....");
	sb.push_back("00....");
	sb.push_back("000000");
	sb.push_back("000000");
	SoftBody::Build(m_physicsScene, glm::vec2(-50, 0), 5.0f, 10.0f, 1, sb);

	std::vector<std::string> sc;
	sc.push_back("..00..");
	sc.push_back("..00..");
	sc.push_back("000000");
	sc.push_back("000000");
	sc.push_back("..00..");
	sc.push_back("..00..");
	SoftBody::Build(m_physicsScene, glm::vec2(0, 0), 5.0f, 10.0f, 1, sc);
	SoftBody::Build(m_physicsScene, glm::vec2(50, 0), 5.0f, 10.0f, 1, sc);
}
