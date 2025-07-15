#include "Game.h"

void Game::setup()
{
	InitWindow(screenWidth, screenHeight, "Gravity Simulation");
}

void Game::loop()
{
	BeginDrawing();
	ClearBackground(BLACK);
	DrawCircle(screenWidth/2, screenHeight/2, 30, WHITE);

	EndDrawing();
}