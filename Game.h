#pragma once
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
	static constexpr int defaultGameSpeed = 10;

	//delta used to not destroy the simulation(ex. while dragging window)
	float safeDelta;

	//how many times the physics is updated in a frame
	int gameSpeed;

	//coordinates to be displayed

	static constexpr int coordinatesSize = 100;
	char coordinates[coordinatesSize];

public:
	~Game()
	{
		CloseWindow();
	}

	Game()
	{
		setup();
		UI.setup();
		camera = { 0 };
		camera.target = Vector2{ 0.0f,0.0f };
		camera.offset = Vector2{ GetScreenWidth() / 2.0f - (GetScreenWidth() - UI.startingX)/2.0f,GetScreenHeight() / 2.0f };
		camera.rotation = 0.0f;
		camera.zoom = 0.5f;
		gamePaused = false;
		frameCounter = 0;
		safeDelta = 0.0f;
		gameSpeed = defaultGameSpeed;
	}


	void setup();
	void loop();
	void addBody(Vector2& position, float mass, Color color);
	void addBody(Vector2& position, float mass, Color color, Vector2& velocity);
	void draw();
	void setTrails();
	void drawTrails();
	void checkWindow();
	void updateCoordinates();
};

