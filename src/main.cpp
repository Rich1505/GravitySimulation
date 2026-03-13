/*
Camera2D
Input
Pausa
Modifica in game
Griglia
Coordinate
*/
#define RAYGUI_IMPLEMENTATION
#include"Game.h"

int main()
{
	Game game;
	
	while (!WindowShouldClose())
	{
		game.loop();
	}
	return 0;
}