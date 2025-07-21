#include "UserInterface.h"
#include<raymath.h>
#include"Physics.h"
#include<iostream>
#include<sstream>
#include<iomanip>

void UserInterface::setup()
{
	startingX = GetScreenWidth() - width;
	texts[0] = UIText{ "SPACE TO PAUSE",10 };
	texts[1] = UIText{ "MOUSE WHEEL TO ZOOM",70 };
	texts[2] = UIText{ "ARROWS TO CHANGE SPEED",130 };
}

void UserInterface::draw(bool gamePaused, char* coordinates,int gameSpeed,int defaultGameSpeed)
{
	DrawRectangle(startingX, 0, GetScreenWidth() - startingX, GetScreenHeight(), color);
	drawText();
	drawGameSpeed(gameSpeed,defaultGameSpeed);

	if (gamePaused)
	{
		DrawText("PAUSED", 5, 5, 40, WHITE);
	}

	DrawText(coordinates, 0, GetScreenHeight() - 20, 20, WHITE);
}

void UserInterface::drawGameSpeed(int gameSpeed, int defaultGameSpeed)
{
	float value = (float)gameSpeed / (float)defaultGameSpeed;
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2) << value;
	std::string str = oss.str();
	str = "x" + str;
	DrawText(str.c_str(), GetScreenWidth() - UI_WIDTH - 52, GetScreenHeight() - 20, 20, WHITE);
}

void UserInterface::drawText()
{
	for (size_t i = 0; i < 3; i++)
	{
		DrawText(texts[i].text.c_str(), texts[i].x, texts[i].y, texts[i].fontSize, WHITE);
	}
}

int counterPressed = 0;
void UserInterface::checkInput(Camera2D &camera, bool &gamePaused, std::vector<Body> &bodies, int &gameSpeed)
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{

	}
	else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		counterPressed++;

		//only if pressed for enough time
		if (counterPressed >= (float)GetFPS()/10.0f)
		{
			Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), camera);
			Vector2 mouseDelta = Vector2Subtract(mousePos, prevMousePos);


			if (Body::selected)
			{
				Body::selected->followMouse(mousePos);
			}
			else
			{

				//check for a collision between the mouse and a body
				for (size_t i = 0; i < bodies.size(); i++)
				{
					if (CheckCollisionPointCircle(mousePos, bodies[i].position, bodies[i].radius))
					{
						Body::selected = &bodies[i];
						bodies[i].followMouse(mousePos);
						break;
					}
				}
			}
		}
	}
	else
	{
		counterPressed = 0;
		Body::selected = nullptr;
	}
	

	if (IsKeyPressed(KEY_SPACE))
	{
		gamePaused = !gamePaused;
	}

	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{
		Vector2 mouseDelta = GetMouseDelta();
		Vector2 delta = Vector2Scale(mouseDelta, -1.0f / camera.zoom);
		camera.target = Vector2Add(camera.target, delta);
	}

	float scrool = GetMouseWheelMove();
	if (scrool != 0)
	{
		float zoomSpeed = 0.1f;
		float prevZoom = camera.zoom;

		camera.zoom += scrool * zoomSpeed;
		camera.zoom = Clamp(camera.zoom, 0.08f, 4.0f);

		Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
		Vector2 offset = Vector2Subtract(mouseWorldPos, camera.target);
		camera.target = Vector2Add(camera.target, Vector2Scale(offset, (1.0f - prevZoom / camera.zoom)));
	}

	if (IsKeyPressed(KEY_UP))
	{
		gameSpeed += 2;
	}
	else if (IsKeyPressed(KEY_DOWN))
	{
		gameSpeed -= 2;
	}

	gameSpeed = Clamp(gameSpeed, 2.0f, 50.0f);

	prevMousePos = GetScreenToWorld2D(GetMousePosition(), camera);
}
