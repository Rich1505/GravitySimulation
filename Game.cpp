#include "Game.h"

void Game::setup()
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "Gravity Simulation");
	SetTargetFPS(144);

	Vector2 pos = { 800.0f,450.0f };
	addBody(pos, 200000.0f, YELLOW);

	pos = { 800.0f,200.0f };
	addBody(pos, 200.0f, WHITE);
	bodies[1].velocity = physics.computeCircularVelocity(bodies[1], bodies[0]);
}

void Game::loop()
{
	checkWindow();
	
	frameCounter++;

	if (!gamePaused)
	{
		physics.update(bodies, safeDelta);
		setTrails();
	}
	

	UI.checkInput(camera,gamePaused,bodies);

	draw();

	safeDelta = Clamp(GetFrameTime(), 0, 0.1f);

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
	BeginDrawing();
	ClearBackground(BLACK);
	BeginMode2D(camera);

	drawTrails();
	for (size_t i = 0; i < bodies.size(); i++)
	{
		bodies[i].draw();
	}

	

	EndMode2D();

	UI.draw(gamePaused);

	DrawFPS(0, 0);

	EndDrawing();
}

float timeElapsed = 0.0f;
int counterTrail = 0;
void Game::setTrails()
{
	timeElapsed += GetFrameTime();
	if (timeElapsed >= 0.05f)
	{
		int start = (counterTrail + 1) % Body::trailSize;

		for (size_t i = 0; i < bodies.size(); i++)
		{
			bodies[i].trail[counterTrail % Body::trailSize] = bodies[i].position;

			for (int j = 0; j < Body::trailSize; j++)
			{
				bodies[i].trailOrdered[j] = bodies[i].trail[(start + j) % Body::trailSize];
			}
		}
		timeElapsed = 0.0f;
		counterTrail++;
	}
}

void Game::drawTrails()
{
	for (size_t i = 0; i < bodies.size(); i++)
	{
		DrawSplineLinear(bodies[i].trailOrdered, Body::trailSize,(1.0f/camera.zoom) ,bodies[i].color);
	}
}

void Game::checkWindow()
{
	if (GetScreenHeight() != screenHeight)
	{
		screenHeight = GetScreenHeight();
	}

	if (GetScreenWidth() != screenWidth)
	{
		screenWidth = GetScreenWidth();
		UI.setup();
	}
}