/*
Camera2D
Input
Pausa
Modifica in game
*/

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