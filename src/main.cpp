#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Variables.hpp"
#include "Texture.hpp"
#include "Map.hpp"
#include "Ground.hpp"
#include "Game.hpp"
#include "MainScreen.hpp"
#include "Instruct.hpp"
bool Init();
void Close();
int Menu();
int Instruction();
int Exit();
int PlayGame();
Game* game;
MainScreen* mainscreen;
Instruct* instruction;
enum Menu{
	PLAYGAME,
	INSTRUCTION,
	EXIT,
	MENU
};

int main(int argc, char *argv[]){
	Init();
	int type = MENU;
    while (type != EXIT){
        game = new Game();
        switch (type){
            case MENU:
                type = Menu();
                break;
            case INSTRUCTION:
                type = Instruction();
                break;
            case EXIT:
                type = Exit();
                break;
            case PLAYGAME:
                type = PlayGame();
                break;
            default:
                break;
        }
        game->Clean();
        delete game;
    }

	Close();
	return 0;
}

bool Init(){
	bool success = true;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
		std::cout << "Khong the khoi tao SDL. Loi: " << SDL_GetError() << std::endl;
		success = false;
	}
	else{
		window = SDL_CreateWindow("Mystery Guy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
		if (window == NULL){
			std::cout << "Khong the tao cua so game! SDL error: " << SDL_GetError() << std::endl;
			success = false;
		}
		else{
			renderer = SDL_CreateRenderer(window, -1, 0);
			if (renderer == NULL){
				std::cout << "Khong the tao but ve! SDL error: " << SDL_GetError() << std::endl;
				success = false;
			}
			else{
				if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)){
					std::cout << "Khong the khoi dong SDL_image! SDL_image error: " << IMG_GetError() << std::endl;
					success = false;
				}
				if (TTF_Init() == -1){
					std::cout << "Khong the khoi dong SDL_ttf! SDL_ttf error: " << TTF_GetError() << std::endl;
					success = false;
				}
				if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
					std::cout << "Khong the khoi dong SDL_mixer! SDl_mixer error: " << Mix_GetError() << std::endl;
					success = false;
				}
			}
		}
	}
	std::string fontPath = "data/Fonts/visitor1.ttf";
	fGame = TTF_OpenFont(fontPath.c_str(), 40);
	return success;
}

int Menu(){
	mainscreen = new MainScreen();
    mainscreen->Init();
	Uint32 start_time = 0, current_time, deltaTime;
	bool quit = false;
    while (!quit){
		SDL_Event event;
		frameStart = SDL_GetTicks();
		current_time = SDL_GetTicks();
		deltaTime = current_time - start_time;
		start_time = current_time;
		int state = mainscreen->Update(deltaTime);
		SDL_RenderClear(renderer);
		while (SDL_PollEvent(&event) != 0){
			if (event.type == SDL_QUIT){
				quit = true;
				return EXIT;
			}
		}
        switch (state){
            case -1:
                mainscreen->Render();
                break;
            case INSTRUCTION:
                return INSTRUCTION;
            case EXIT:
                return EXIT;
            case PLAYGAME:
                return PLAYGAME;
            default:
                break;
        }
		SDL_RenderPresent(renderer);
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
		SDL_Delay(frameDelay - frameTime);
    }
    return -1;
}

int PlayGame(){
	bool quit = false, quitGame = false; int currentstate = -1;
	Uint32 start_time = 0, current_time, deltaTime;
	Game* game = new Game();
	while (!quit){
		SDL_Event event;
		if (quitGame) break;
		game->Init();
		while (!quitGame){
			frameStart = SDL_GetTicks();
			SDL_RenderClear(renderer);
			current_time = SDL_GetTicks();
			deltaTime = current_time - start_time;
			deltaTime = std::min(deltaTime, (Uint32) 16);
			start_time = current_time;
			while (SDL_PollEvent(&event) != 0){
				if (event.type == SDL_QUIT){
					quitGame = true;
					quit = true;
					return EXIT;
				}
				else {
					if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
						if (currentstate == -1) currentstate = 1;
						else currentstate = -1;
					}
					if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN && currentstate == 1 && event.key.repeat == 0) 
						return MENU;
				}
			}
	     	if (currentstate != 1) game->Update(deltaTime);
			if (game->isWinGame()){
				game->RenderGameWin();
				const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    			if (currentKeyStates[SDL_SCANCODE_RETURN]) return MENU; 
			}
			else{
				if (game->isLoseGame()){
					game->RenderGameOver();
					const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    				if (currentKeyStates[SDL_SCANCODE_RETURN]) return MENU; 
				}
				else {
					if (currentstate == 1) game->RenderGamePause();
					else game->Render();
				}
			}
			SDL_RenderPresent(renderer);
			frameTime = SDL_GetTicks() - frameStart;
			if (frameDelay > frameTime)
				SDL_Delay(frameDelay - frameTime);
		}
	}
	return -1;
}

int Instruction(){
	instruction = new Instruct();
    instruction->Init();
	Uint32 start_time = 0, current_time, deltaTime;
	bool quit = false;
    while (!quit){
		SDL_Event event;
		frameStart = SDL_GetTicks();
		current_time = SDL_GetTicks();
		deltaTime = current_time - start_time;
		start_time = current_time;
		SDL_RenderClear(renderer);
		while (SDL_PollEvent(&event) != 0){
			if (event.type == SDL_QUIT){
				quit = true;
				return EXIT;
			}
			else{
				 if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) return MENU;
			}
		}
		instruction->Render();
		SDL_RenderPresent(renderer);
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
		SDL_Delay(frameDelay - frameTime);
    }
    return -1;
}
int Exit(){
	return EXIT;
}

void Close(){
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	window = nullptr;
	renderer = nullptr;
	Mix_CloseAudio();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}