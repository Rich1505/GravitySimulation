#pragma once
#include<vector>
#include"Body.h"
#include<string>
#include<iostream>
#include<raygui.h>

constexpr int UI_WIDTH = 400;

struct MassSelector {
	
	static constexpr int minValue = 200;
	static constexpr int maxValue = 1000000000;
	static constexpr int width = 300;
	Rectangle rec;
	char text[10];
	int prevValue;
	int value;

	MassSelector()
		:rec{ 0,0,0,0}, value(200),prevValue(200), text("") { }

	void draw(int offsetY)
	{
		Rectangle temp = rec;
		temp.y = temp.y + offsetY;
		GuiValueBox(temp, text, &value, minValue, maxValue, true);
		update();
	}

	void update()
	{
		int k = GetKeyPressed();

		if (k != KEY_BACKSPACE && k != 0)
		{
			char number[11];
			strcpy(number,_itoa(value, number, 10));

			int i = strlen(number);

			if (i >= 10)
			{
				value = prevValue;
				return;
			}
		}
		prevValue = value;
	}
};

struct Slider {
	Rectangle range;
	Rectangle selector;
	int maxValue;
	int minValue;
	int value;
	int width = 800;

	Slider(Rectangle range, Rectangle selector,int maxValue, int minValue)
		:range(range), selector(selector), maxValue(maxValue), minValue(minValue)
	{
		value = (int)Remap((float)range.x + range.width / 2, (float)range.x, (float)range.x + range.width, (float)minValue, (float)maxValue);
		this->selector.y = selector.y - (selector.height - range.height) / 2;
	}

	Slider(int width)
		:range{ 0,0,0,0 }, selector{ 0,0,0,0 }, maxValue(0), minValue(0), value(0),width(width) {}

	Slider()
		:range{ 0,0,0,0 }, selector{ 0,0,0,0 }, maxValue(0), minValue(0), value(0), width(0) {}

	bool checkCollision(Vector2 mousePos)
	{
		return CheckCollisionPointRec(mousePos, selector);
	}

	void changePosition(Vector2 mousePos)
	{
		if (mousePos.x < range.x + range.width && mousePos.x > range.x)
		{
			
			selector.x = mousePos.x - selector.width/2;
			value = (int)Remap((float)selector.x+selector.width/2.0f, (float)range.x, (float)range.x + range.width, (float)minValue, (float)maxValue);
			if (abs(selector.x + selector.width / 2 - range.x) <=2)
			{
				value = minValue;
			}
			else if(abs(selector.x + selector.width / 2 - (range.x + range.width)) <= 2)
			{
				value = maxValue;
			}

			std::cout << "Mass: " << value << std::endl;
			std::cout << selector.x + selector.width / 2;
		}
	}

	void draw(int offsetY)
	{
		Rectangle temp = range;
		temp.y = temp.y + offsetY;
		DrawRectangleRec(temp, Color{ 0,0,0,100 });
		temp = selector;
		temp.y = temp.y + offsetY;
		DrawRectangleRec(temp, Color{ 200,200,200,200 });
	}
};

struct Button {
	Rectangle rec;
	Color color;
	
	static constexpr int width = 100;
	static constexpr int height = 100;
	static constexpr int spaceX = 50;
	static constexpr int spaceY = 50;
	static constexpr int startingY = 200;

	Button(Color color)
		:rec{0, 0, width, height}, color{color.r, color.g, color.b, 200} {}

	Button() 
		:rec{ 0,0,0,0 }, color{ 0,0,0 } {}

	void draw(int offsetY)
	{
		Rectangle temp = rec;
		temp.y = temp.y + offsetY;
		//DrawRectangle(rec.x,rec.y + offsetY,rec.width,rec.height, Color{ 0,0,0,100 });
		DrawRectangleRounded(temp, 0.2f, 10, Color{ 0,0,0,100 });
		DrawCircle((int)(rec.x + rec.width / 2), (int)(rec.y + rec.height / 2 + offsetY), rec.width/2.0f - 5.0f, color);
	}

	void drawSelected(int offsetY)
	{
		Rectangle temp = rec;
		temp.y = temp.y + offsetY;
		DrawRectangleRoundedLines(temp, 0.2f, 60, WHITE);
	}
};

struct UIText {
	static constexpr int fontSize = 20;

	std::string text;
	int width;
	int x;
	int y;

	UIText(const char text[], int y) 
		:text(text), width(MeasureText(text, fontSize)), x((GetScreenWidth() - UI_WIDTH) + (UI_WIDTH - width) / 2), y(y){}

	UIText() 
		:text(""), width(0), x(0), y(0){}

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
	UIText texts[4];
	Button buttons[6];
	MassSelector massSelector;

public:
	int selectedButton;
	static constexpr int numberOfButtons = 6;
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
	void massSelectorSetup();

	UserInterface()
	{
		selectedButton = -1;
		startingX = 0;
		color = Color{ 100,100,100,200};
		prevMousePos = { 0.0f,0.0f };
		offsetY = 0;
	}
};
