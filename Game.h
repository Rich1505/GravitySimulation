#pragma once
#include<raylib.h>
#include<iostream>

class Game
{
private:
	const int screenWidth = 1600;
	const int screenHeight = 900;

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

