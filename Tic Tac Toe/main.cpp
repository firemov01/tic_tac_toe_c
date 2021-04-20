#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "Game.h"

//Screen dimension constants
const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 400;

Game* game = nullptr;

int main(int argc, char* args[]) {
	game = new Game();
	game->init("Tic Tac Toe", SCREEN_WIDTH, SCREEN_HEIGHT);

	while (game->running())
	{
		game->handleEvents();
		game->update();
	}

	game->clean();
	return 0;
}