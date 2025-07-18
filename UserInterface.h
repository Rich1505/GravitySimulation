#pragma once
#include<raylib.h>
#include<vector>
#include"Body.h"

class UserInterface
{
private:
	Color color;
	Vector2 prevMousePos;
	Body* prev;

public:
	int startingX;
	void draw(bool gamePaused);
	void setup();
	void checkInput(Camera2D &camera, bool &gamePaused, std::vector<Body> &bodies);

	UserInterface()
	{
		startingX = 0;
		color = Color{ 100,100,100,200};
		prevMousePos = { 0.0f,0.0f };
		prev = nullptr;
	}
};

