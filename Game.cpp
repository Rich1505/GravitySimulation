#include "Game.h"

void Game::setup()
{
	InitWindow(screenWidth, screenHeight, "Gravity Simulation");

	Vector2 pos = { 800.0f,450.0f };
	physics.addBody(pos, 20000.0f, 50.0f, YELLOW);

	pos = { 800.0f,200.0f };
	Vector2 velocity = { 8.94f,0.0f };
	physics.addBody(pos, 10.0f, 20.0f, WHITE,velocity);
}

void Game::loop()
{
	BeginDrawing();
	ClearBackground(BLACK);
	physics.update();
	EndDrawing();
}