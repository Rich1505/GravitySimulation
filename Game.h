#pragma once
#include<raylib.h>
#include<iostream>
#include"Physics.h"
#include<vector>
#include"UserInterface.h"

class Game
{
private:
	int screenWidth = 1600;
	int screenHeight = 900;
	Physics physics;
	std::vector<Body> bodies;
	Camera2D camera;
	UserInterface UI;
	bool gamePaused;
	int frameCounter;
	float safeDelta;

public:
	~Game()
	{
		CloseWindow();
	}

	Game()
	{
		setup();
		camera = { 0 };
		camera.target = bodies[0].position;
		camera.offset = Vector2{ GetScreenWidth() / 2.0f,GetScreenHeight() / 2.0f };
		camera.rotation = 0.0f;
		camera.zoom = 1.0f;
		UI.setup();
		gamePaused = false;
		frameCounter = 0;
		safeDelta = 0.0f;
	}


	void setup();
	void loop();
	void addBody(Vector2& position, float mass, Color color);
	void addBody(Vector2& position, float mass, Color color, Vector2& velocity);
	void draw();
	void setTrails();
	void drawTrails();
	void checkWindow();
};

