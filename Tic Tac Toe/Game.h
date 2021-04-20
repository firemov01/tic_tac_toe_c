#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "Button.h"
#include "circle.h"

class Game
{
public:
	Game();
	~Game();

	//Starts up SDL and creates window
	bool init(const char* WindowName, int window_width, int window_height);

	bool loadMedia();
	SDL_Surface* loadSurface(std::string path);
	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void clean();

	//Frees media and shuts down SDL
	void close();

	//Loads individual image as texture
	SDL_Event event;
	bool isRunning;
	SDL_Renderer* gRenderer=NULL;

	int mouseY, mouseX;
	void startGame();
	void nextRound();
	bool checkForWin();
	bool tableIsFull();

	void drawX(int x, int y);
	void drawO(int x, int y);

private:
	enum WImage
	{
		Owin,
		Xwin,
		draw
	};
	int round = 0;
	Button* box[3][3];
	SDL_Window* gWindow = NULL;
	SDL_Surface* gEndSurfaces[3];
	SDL_Surface* gCurrentSurface = NULL;
	SDL_Surface* gScreenSurface = NULL;
};

