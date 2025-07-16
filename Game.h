#pragma once
#include<raylib.h>
#include<iostream>
#include"Physics.h"
#include<vector>

class Game
{
private:
	const int screenWidth = 1600;
	const int screenHeight = 900;
	Physics physics;
	std::vector<Body> bodies;

public:
	~Game()
	{
		std::cout << "Chiuso";
		CloseWindow();
	}

	Game()
	{
		setup();
	}


	void setup();
	void loop();
	void addBody(Vector2& position, float mass, Color color);
	void addBody(Vector2& position, float mass, Color color, Vector2& velocity);
	void draw();
};

