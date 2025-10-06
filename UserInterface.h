#pragma once
#include<raylib.h>
#include<vector>
#include"Body.h"
#include<string>
#include<iostream>

constexpr int UI_WIDTH = 400;

struct Button {
	Rectangle rec;
	Color color;
	
	static constexpr int width = 100;
	static constexpr int height = 100;
	static constexpr int spaceX = 50;
	static constexpr int spaceY = 50;
	static constexpr int startingY = 200;

	Button(Color color)
	{
		rec.width = width;
		rec.height = height;
		this->color = Color{color.r,color.g,color.b,200};
	}

	Button()
	{
		rec = Rectangle{ 0,0,0,0 };
		color = Color{ 0,0,0 };
	}

	void draw(int offsetY)
	{
		Rectangle temp = rec;
		temp.y = temp.y + offsetY;
		//DrawRectangle(rec.x,rec.y + offsetY,rec.width,rec.height, Color{ 0,0,0,100 });
		DrawRectangleRounded(temp, 0.2f, 0, Color{ 0,0,0,100 });
		DrawCircle((int)(rec.x + rec.width / 2), (int)(rec.y + rec.height / 2 + offsetY), rec.width / 2 - 5, color);
	}
};

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

	void draw(int offsetY)
	{
		DrawText(text.c_str(), x, y + offsetY, fontSize, WHITE);
	}
};

class UserInterface
{
private:
	Color color;
	//mouse position in the previous frame translated in world coordinates
	Vector2 prevMousePos;
	UIText texts[3];
	Button buttons[6];

public:
	static constexpr int defaultHeight = 900;
	int startingX;
	int offsetY;
	static constexpr int width = UI_WIDTH;
	void draw(bool gamePaused,char* coordinates,int gameSpeed,int defaultGameSpeed);
	void drawText();
	void drawButtons();
	void drawGameSpeed(int gameSpeed, int defaultGameSpeed);
	void setup();
	void buttonSetup();
	void checkInput(Camera2D &camera, bool &gamePaused, std::vector<Body> &bodies, int &gameSpeed);

	UserInterface()
	{
		startingX = 0;
		color = Color{ 100,100,100,200};
		prevMousePos = { 0.0f,0.0f };
		offsetY = 0;
	}
};

