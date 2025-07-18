#include "UserInterface.h"
#include<raymath.h>
#include"Physics.h"
#include<iostream>

void UserInterface::setup()
{
	startingX = GetScreenWidth() - 300;
}

void UserInterface::draw(bool gamePaused)
{
	DrawRectangle(startingX, 0, GetScreenWidth() - startingX, GetScreenHeight(), color);

	if (gamePaused)
	{
		DrawText("PAUSED", 5, 5, 40, WHITE);
	}
}

int counterPressed = 0;
void UserInterface::checkInput(Camera2D &camera, bool &gamePaused, std::vector<Body> &bodies)
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{

	}
	else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		counterPressed++;
		if (counterPressed >= (float)GetFPS()/10.0f)
		{
			Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), camera);
			Vector2 mouseDelta = Vector2Subtract(mousePos, prevMousePos);


			if (prev)
			{
				prev->followMouse(mousePos,gamePaused);
			}
			else
			{
				for (size_t i = 0; i < bodies.size(); i++)
				{
					if (CheckCollisionPointCircle(mousePos, bodies[i].position, bodies[i].radius))
					{
						bodies[i].followMouse(mousePos,gamePaused);
						prev = &bodies[i];
						break;
					}
				}
			}
		}
	}
	else
	{
		prev = nullptr;
		counterPressed = 0;
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
	prevMousePos = GetScreenToWorld2D(GetMousePosition(), camera);
}
