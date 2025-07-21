#include "Game.h"
#include<iostream>
#include<string>

void Game::setup()
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "Gravity Simulation");
	SetWindowMinSize(600, 450);

	SetTargetFPS(144);

	Vector2 pos = { 0.0f,0.0f };
	addBody(pos, 200000.0f, YELLOW);

	pos = { 0.0f,-250.0f };
	addBody(pos, 200.0f, WHITE);
	bodies[1].velocity = physics.computeCircularVelocity(bodies[1], bodies[0]);
}

//frame logic
void Game::loop()
{
	updateCoordinates();
	checkWindow();
	
	frameCounter++;

	if (!gamePaused)
	{
		for(size_t i = 0;i<gameSpeed;i++)
			physics.update(bodies, safeDelta);

		setTrails();
	}
	

	UI.checkInput(camera,gamePaused,bodies,gameSpeed);

	draw();

	//maximum delta = 0.1f
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

	UI.draw(gamePaused,coordinates,gameSpeed,defaultGameSpeed);
	
	DrawFPS(0, 0);

	EndDrawing();
}

//to update trails based on the time
float timeElapsed = 0.0f;

//actual starting point from the trail vector
int counterTrail = 0;

//update the bodies' trails
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

//draw the bodies' trails
void Game::drawTrails()
{
	for (size_t i = 0; i < bodies.size(); i++)
	{
		DrawSplineLinear(bodies[i].trailOrdered, Body::trailSize,(1.0f/camera.zoom) ,bodies[i].color);
	}
}

//update the screen variables if they've changed
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

//update the displayed coordinates
void Game::updateCoordinates()
{
	std::string x = std::to_string(int(camera.target.x));
	std::string y = std::to_string(int(camera.target.y));

	std::string final = x + "," + y;
	
	for (size_t i = 0; i < final.size() && i < coordinatesSize; i++)
	{
		coordinates[i] = final[i];
	}

	coordinates[final.size()] = '\0';
}