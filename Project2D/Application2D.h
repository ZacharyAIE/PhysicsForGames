#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "PhysicsScene.h"

/// <summary>
/// This class is responsible for initialising, drawing and updating the simulation's window.
/// </summary>

class Application2D : public aie::Application {
public:

	Application2D();

	virtual ~Application2D();

	/// <summary>
	/// Initialises the simulation. Set gravity and other settings here.
	/// </summary>
	/// <returns> Returns completion status</returns>
	virtual bool startup();

	/// <summary>
	/// Runs at shutdown. Primarily responsible for memory cleanup
	/// </summary>
	virtual void shutdown();
	
	/// <summary>
	/// The update function is responsible for providing the simulation with a place to update values each frame.
	/// </summary>
	/// <param name="deltaTime"></param>
	virtual void update(float deltaTime);

	/// <summary>
	/// The draw function is called each update cycle per object that overrides it. This is responsible for the drawing of objects to the screen.
	/// </summary>
	virtual void draw();

	/// <summary>
	/// Used to convert mouse click locations to world space for interactions.
	/// </summary>
	/// <param name="screenPos"></param>
	/// <returns></returns>
	glm::vec2 screenToWorld(glm::vec2 screenPos);

	/// <summary>
	/// Used to spawn the bounce test scene.
	/// </summary>
	void SpawnBounceTest();

	/// <summary>
	/// Used to spawn the original contact force test.
	/// </summary>
	void SpawnContactForceTest();

	/// <summary>
	///  Used to spawn the rope test scene.
	/// </summary>
	/// <param name="num"></param>
	void Rope(int num);

	/// <summary>
	/// Used to spawn the spring test scene.
	/// </summary>
	void SpringTest();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Texture*		m_texture;
	aie::Texture*		m_shipTexture;
	aie::Font*			m_font;
	PhysicsScene*		m_physicsScene;
	const float extents = 100;
	const float aspectRatio = 16.0f / 9.0f;

	float m_timer;
};