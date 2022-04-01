#include "RenderWindow.h"
#include "GTexture.h"
#include "Character.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <fstream>
#include <string>

SDL_Window* gWindow;
SDL_Renderer* gRenderer;

const int SPEED = 30;

bool init(){
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL_Init has failed. Error: " << SDL_GetError() << std::endl;
	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;
	if (!(TTF_Init()))
		std::cout << "TTF_init has failed. Error: " << SDL_GetError() << std::endl;
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	return true;
}

bool SDLinit = init();
LTexture mainMap;
Character mainChar(1000, 1000);
SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
Tile* tileSet[TOTAL_TILES];

void loadMapFile(){
	int x = 0;
	int y = 0;

	std::ifstream map("res/data/map.txt");	

	if (map.fail()){
		std::cout << "Couldn't open Map File!" << std::endl;
		return ;
	}

	for (int i = 1; i <= TOTAL_TILES_ROW; i++){
		for (int j = 1; j <= TOTAL_TILES_COL; j++){
			int typeTile = -1;
			map >> typeTile;

			if (map.fail()){
				std::cout << "Unexpected end of file!" << std::endl;
				return;
			}

			if ((typeTile >= 0) && (typeTile < TOTAL_TILE_SPRITES)) {
				tileSet[getPos(i, j)] = new Tile(x, y, typeTile);
			}
			else{
				std::cout << "Map has invaild type!" << std::endl;
			}

			x = x + TILE_WIDTH;

			if (x >= LEVEL_WIDTH){
				x = 0;
				y = y + TILE_HEIGHT;
			}
		}
	}
	map.close();
}

void loadMedia(){
	mainMap.loadFromFile("res/gfx/map.png", gRenderer);
	mainChar.gChaTexture.loadFromFile("res/gfx/char.png", gRenderer);
}


int main(int argc, char* args[]){

	SDLinit &= initWindow(gWindow, gRenderer);
	if (!SDLinit){
		std::cout << "Failed to initialize!" << std::endl;
	}
	else{
		
		bool quit = false;
		SDL_Event e;
		
		loadMedia();
		loadMapFile();

		while (!quit){
			
			while (SDL_PollEvent(&e) != 0){
				if (e.type == SDL_QUIT){
					quit = true;
				}
				mainChar.handleEvent(e);

			}
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gRenderer);

			mainChar.move(tileSet);
			mainChar.setCamera(camera);
			//mapp.render(x, y, gRenderer);
			mainMap.render(-camera.x, -camera.y, gRenderer);
			mainChar.render(camera, gRenderer);
			SDL_RenderPresent(gRenderer);
		}	
	}
	SDL_DestroyWindow(gWindow);
	SDL_Quit();
	TTF_Quit();
	return 0;
}