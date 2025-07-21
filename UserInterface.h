#pragma once
#include<raylib.h>
#include<vector>
#include"Body.h"
#include<string>
#include<iostream>

constexpr int UI_WIDTH = 400;

struct UIText {
	static constexpr int fontSize = 20;

	std::string text;
	int width;
	int x;
	int y;

	UIText(const char text[], int y)
	{
		this->text = text;
		width = MeasureText(text, fontSize);
		x = (GetScreenWidth() - UI_WIDTH) + (UI_WIDTH-width)/2;
		this->y = y;
	}

	UIText()
	{
		text = "";
		width = 0;
		x = 0;
		y = 0;
	}
};

class UserInterface
{
private:
	Color color;
	int offsetY;
	//mouse position in the previous frame translated in world coordinates
	Vector2 prevMousePos;
	UIText texts[3];

public:
	int startingX;
	static constexpr int width = UI_WIDTH;
	void draw(bool gamePaused,char* coordinates,int gameSpeed,int defaultGameSpeed);
	void drawText();
	void drawGameSpeed(int gameSpeed, int defaultGameSpeed);
	void setup();
	void checkInput(Camera2D &camera, bool &gamePaused, std::vector<Body> &bodies, int &gameSpeed);

	UserInterface()
	{
		startingX = 0;
		color = Color{ 100,100,100,200};
		prevMousePos = { 0.0f,0.0f };
		offsetY = 0;
	}
};

