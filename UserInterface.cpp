#include "UserInterface.h"
#include<raymath.h>
#include"Physics.h"
#include<iostream>
#include<sstream>
#include<iomanip>

//prototype
bool checkCollisionMouseButton(Button button, Vector2 mousePos);

void UserInterface::setup()
{
	startingX = GetScreenWidth() - width;
	texts[0] = UIText{ "SPACE TO PAUSE",10 };
	texts[1] = UIText{ "MOUSE WHEEL TO ZOOM",70 };
	texts[2] = UIText{ "ARROWS TO CHANGE SPEED",130 };

	buttons[0] = Button{ WHITE };
	buttons[1] = Button{ YELLOW };
	buttons[2] = Button{ GREEN };
	buttons[3] = Button{ BLUE };
	buttons[4] = Button{ PURPLE };
	buttons[5] = Button{ BROWN };

	buttonSetup();
}

void UserInterface::buttonSetup()
{
	int totalSpaceWidth = Button::spaceX + Button::width * 2;
	int x = (UI_WIDTH - totalSpaceWidth) / 2;

	for (size_t i = 0; i < 3; i++)
	{
			buttons[i * 2].rec.x = (float)(UserInterface::startingX + x);
			buttons[i * 2 + 1].rec.x = (float)(UserInterface::startingX + x + Button::width + Button::spaceX);
			buttons[i * 2].rec.y = (float)(Button::startingY + i * Button::spaceY + i * Button::height);
			buttons[i * 2 + 1].rec.y = (float)(Button::startingY + i * Button::spaceY + i * Button::height);
			//std::cout << buttons[i * j].rec.x << " " << buttons[i * j].rec.y << " " << i << " " << j << std::endl << buttons[i * j + 1].rec.x << " " << buttons[i * j + 1].rec.y << std::endl;
	}
}

void UserInterface::draw(bool gamePaused, char* coordinates,int gameSpeed,int defaultGameSpeed)
{
	DrawRectangle(startingX, 0, GetScreenWidth() - startingX, GetScreenHeight(), color);
	drawText();
	drawButtons();
	drawGameSpeed(gameSpeed,defaultGameSpeed);

	if (gamePaused)
	{
		DrawText("PAUSED", 5, 5, 40, WHITE);
	}

	DrawText(coordinates, 0, GetScreenHeight() - 20, 20, WHITE);
}

void UserInterface::drawButtons()
{
	for (size_t i = 0; i < 6; i++)
	{
		buttons[i].draw(offsetY);

		if (i == selectedButton)
			buttons[i].drawSelected(offsetY);
	}
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
		texts[i].draw(offsetY);
	}
}

int counterPressedLeftMouseButton = 0;
void UserInterface::checkInput(Camera2D &camera, bool &gamePaused, std::vector<Body> &bodies, int &gameSpeed)
{
	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
	{
		//check if the left mouse button was pressed for a short time
		//interaction with the buttons
		if (counterPressedLeftMouseButton < (GetFPS() * 20.0f)/144)
		{
			Vector2 mousePos = GetMousePosition();
			for (size_t i = 0; i < numberOfButtons; i++)
			{
				if (checkCollisionMouseButton(buttons[i], mousePos))
				{
					selectedButton = (int)i;
					//std::cout << "Selected button: " << selectedButton << std::endl;
					return;
				}
			}

			if(selectedButton == -1)
				return;

			//check if the mouse is not over the UI and add body
			Rectangle UserInterfaceRect = Rectangle{ (float)startingX, 0, (float)(GetScreenWidth() - startingX), (float)GetScreenHeight() };
			if (!CheckCollisionPointRec(mousePos, UserInterfaceRect))
			{
				Color color = buttons[selectedButton].color;
				color.a = 255;
				bodies.push_back(Body{ GetScreenToWorld2D(mousePos,camera),100.0f,color });
			}
		}
	}
	else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		counterPressedLeftMouseButton++;

		//only if pressed for enough time
		if (counterPressedLeftMouseButton >= (float)GetFPS()/10.0f)
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
		counterPressedLeftMouseButton = 0;
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

	float scroll = GetMouseWheelMove();
	if (scroll != 0)
	{
		if (CheckCollisionPointRec(GetMousePosition(), Rectangle{ (float)startingX,0,UI_WIDTH,(float)GetScreenHeight() }))
		{
			int scrollSpeed = 50;
			offsetY += (int)(scrollSpeed * scroll);
			if (offsetY > 0)
				offsetY = 0;

			int advancingPixel = defaultHeight - GetScreenHeight();
			if (offsetY <= -advancingPixel)
			{
				offsetY = -advancingPixel;
			}
		}
		else
		{
			float zoomSpeed = 0.1f;
			float prevZoom = camera.zoom;

			camera.zoom += scroll * zoomSpeed;
			camera.zoom = Clamp(camera.zoom, 0.08f, 4.0f);

			Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
			Vector2 offset = Vector2Subtract(mouseWorldPos, camera.target);
			camera.target = Vector2Add(camera.target, Vector2Scale(offset, (1.0f - prevZoom / camera.zoom)));
		}
		
	}

	if (IsKeyPressed(KEY_UP))
	{
		gameSpeed += 2;
	}
	else if (IsKeyPressed(KEY_DOWN))
	{
		gameSpeed -= 2;
	}

	gameSpeed = (int)Clamp((float)gameSpeed, 2.0f, 50.0f);

	prevMousePos = GetScreenToWorld2D(GetMousePosition(), camera);
}

bool checkCollisionMouseButton(Button button, Vector2 mousePos)
{
	return CheckCollisionPointRec(mousePos, button.rec);
}