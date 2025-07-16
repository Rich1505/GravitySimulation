#include "Game.h"

void Game::setup()
{
	InitWindow(screenWidth, screenHeight, "Gravity Simulation");

	Vector2 pos = { 800.0f,450.0f };
	addBody(pos, 20000.0f, YELLOW);

	pos = { 800.0f,200.0f };
	addBody(pos, 2000.0f, WHITE);
	bodies[1].velocity = physics.computeCircularVelocity(bodies[1], bodies[0]);
}

void Game::loop()
{
	physics.update(bodies);

	BeginDrawing();
	ClearBackground(BLACK);
	draw();
	EndDrawing();
}

void Game::addBody(Vector2& position, float mass, Color color)
{
	bodies.push_back(Body{ position,mass,color });
}

void Game::addBody(Vector2& position, float mass, Color color, Vector2& velocity)
{
	bodies.push_back(Body{ position,mass,color,velocity });
}

void Game::draw()
{
	for (size_t i = 0; i < bodies.size(); i++)
	{
		bodies[i].draw();
	}
}