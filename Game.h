#pragma once
#include<raylib.h>
#include<iostream>
#include"Physics.h"

class Game
{
private:
	const int screenWidth = 1600;
	const int screenHeight = 900;
	Physics physics;

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
};

