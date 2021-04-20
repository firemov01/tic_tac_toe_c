#include "Game.h"

Game::Game()
{}

Game::~Game()
{}

bool Game::init(const char* WindowName, int window_width, int window_height)
{	
	//Initialization flag
	bool success = true;

	//Initialize SDL

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow(WindowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			if (!loadMedia())
			{
				printf("Failed to load media!\n");
			}
			else {	
				gScreenSurface = SDL_GetWindowSurface(gWindow);
				//Create renderer for window
				gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
				if (gRenderer == NULL)
				{
					printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
					success = false;
				}
				startGame();
				isRunning = true;
			}
		}
	}
	
	return success;
}

void Game::nextRound() {
	if (round == 0) {
		round = 1;
	}
	else if (round == 1) {
		round = 0;
	}
}

void Game::close()
{
	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void Game::handleEvents()
{
	//Handle events on queue
	while (SDL_PollEvent(&event) != 0)
	{
		//User requests quit
		if (event.type == SDL_QUIT)
		{
			isRunning = false;
		}

		//Mouse event -> mouse movement
		
		if (event.type == SDL_MOUSEBUTTONDOWN) {

			if (event.button.button == SDL_BUTTON_LEFT) {
				SDL_GetMouseState(&mouseX, &mouseY);
				for (int bx = 0; bx < 3; bx++)
				{
					for (int by = 0; by < 3; by++) {
						if (box[bx][by]->insideButton(mouseX, mouseY)) {
							if (round == 0 && box[bx][by]->getStatus() == 2) {
								box[bx][by]->setStatus(0);
								drawO(bx * 100, by * 100);
								nextRound();
							}
							else if (round == 1 && box[bx][by]->getStatus() == 2) {
								box[bx][by]->setStatus(1);
								drawX(bx * 100, by * 100);
								nextRound();
							}
							if (checkForWin()) {
								if (round==0)
								{
									gCurrentSurface = gEndSurfaces[Xwin];
								}
								else if (round == 1) {
									gCurrentSurface = gEndSurfaces[Owin];
									}
								SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
								SDL_UpdateWindowSurface(gWindow);
								SDL_Delay(3000);
								startGame();

							}
							if (tableIsFull())
							{
								gCurrentSurface = gEndSurfaces[draw];
								SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
								SDL_UpdateWindowSurface(gWindow);
								SDL_Delay(3000);
								startGame();
							}
						}
					}
				}
			}
		}
	}
}

void Game::startGame() {
	SDL_SetRenderDrawColor(gRenderer, 0x58, 0xD6, 0x8D, 0xFF);
	SDL_RenderClear(gRenderer);
	SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xFF, 0xFF);

	for (int x = 0; x < 2; x++)
	{
		for (int y = 0; y < 2; y++)
		{
			SDL_RenderDrawLine(gRenderer, (((y + 1) * 100) * x + 50), (((y + 1) * 100) * std::abs(x - 1) + 50), (400 + ((y - 2) * 100) * x - 50), (400 + ((y - 2) * 100) * std::abs(x - 1) - 50));
		}

	}
	SDL_RenderPresent(gRenderer);
	for (int bx = 0; bx < 3; bx++)
	{
		for (int by = 0; by < 3; by++) {
			box[bx][by] = new Button(100, 100);
			box[bx][by]->setPosition(bx * 100 + 50, by * 100 + 50);
			box[bx][by]->setStatus(2);
		}
	}
}

void Game::update()
{
	//SDL_UpdateWindowSurface(gWindow);
	//SDL_RenderPresent( gRenderer );
}

void Game::clean()
{
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	SDL_Quit();
}

bool Game::checkForWin() {
	if (box[0][0]->getStatus() == box[0][1]->getStatus() && box[0][1]->getStatus() == box[0][2]->getStatus() && box[0][2]->getStatus() != 2) {
		return true;
	}
	else if (box[1][0]->getStatus() == box[1][1]->getStatus() && box[1][1]->getStatus() == box[1][2]->getStatus() && box[1][2]->getStatus() != 2) {
		return true;
	}
	else if (box[2][0]->getStatus() == box[2][1]->getStatus() && box[2][1]->getStatus() == box[2][2]->getStatus() && box[2][2]->getStatus() != 2) {
		return true;
	}


	else if (box[0][0]->getStatus() == box[1][0]->getStatus() && box[1][0]->getStatus() == box[2][0]->getStatus() && box[2][0]->getStatus() != 2) {
		return true;
	}
	else if (box[0][1]->getStatus() == box[1][1]->getStatus() && box[1][1]->getStatus() == box[2][1]->getStatus() && box[2][1]->getStatus() != 2) {
		return true;
	}
	else if (box[0][2]->getStatus() == box[1][2]->getStatus() && box[1][2]->getStatus() == box[2][2]->getStatus() && box[2][2]->getStatus() != 2) {
		return true;
	}

	else if (box[0][0]->getStatus() == box[1][1]->getStatus() && box[1][1]->getStatus() == box[2][2]->getStatus() && box[2][2]->getStatus() != 2) {
		return true;
	}
	else if (box[0][2]->getStatus() == box[1][1]->getStatus() && box[1][1]->getStatus() == box[2][0]->getStatus() && box[2][0]->getStatus() != 2) {
		return true;
	}

	return false;
}

bool Game::tableIsFull() {
	for (int bx = 0; bx < 3; bx++)
	{
		for (int by = 0; by < 3; by++) {
			if (box[bx][by]->getStatus()==2)
			{
				return false;
			}
		}
	}
	return true;
}

void Game::drawX(int x, int y) {
	x += 50;
	y += 50;
	SDL_RenderDrawLine(gRenderer, x + 5, y + 5, x + 95, y + 95);
	SDL_RenderDrawLine(gRenderer, x + 95, y + 5, x + 5, y + 95);
	SDL_RenderPresent(gRenderer);
}

void Game::drawO(int x, int y) {
	glm::vec2 center; center.x = x + 100; center.y = y + 100;
	Circle* o = new Circle(40, center, glm::vec4(255.0f, 255.0f, 255.0f, 255.0f));
	SDL_DrawCircle(gRenderer, *o);
	delete o;
	SDL_RenderPresent(gRenderer);
}

SDL_Surface* Game::loadSurface(std::string path)
{
	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}

	return loadedSurface;
}

bool Game::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load Owin surface
	gEndSurfaces[Owin] = loadSurface("Owin.bmp");
	if (gEndSurfaces[Owin] == NULL)
	{
		printf("Failed to load default image!\n");
		success = false;
	}

	//Load Xwin surface
	gEndSurfaces[Xwin] = loadSurface("Xwin.bmp");
	if (gEndSurfaces[Xwin] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}

	//Load draw surface
	gEndSurfaces[draw] = loadSurface("draw.bmp");
	if (gEndSurfaces[draw] == NULL)
	{
		printf("Failed to load down image!\n");
		success = false;
	}

	return success;
}