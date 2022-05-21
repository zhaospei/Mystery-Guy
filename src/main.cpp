#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Variables.hpp"
#include "Texture.hpp"
#include "Map.hpp"
#include "Ground.hpp"
int theLast = 0;

Map mainMap;
bool init();
void close();
int main(int argc, char *argv[]){
	if (!init())
		std::cout << "Khoi tao chuong trinh that bai..." << std::endl;
	else{
		bool quit = false, quitGame = false;
		std::string fontPath = "data/Fonts/visitor1.ttf";
		fGame = TTF_OpenFont(fontPath.c_str(), 40);
		Uint32 start_time = 0, current_time, deltaTime;
		mainMap.loadMapFile("data/map/3.txt");
		mainMap.loadTexture();
		while (!quit){
			SDL_Event event;
			// Vòng lặp của game
			while (!quitGame){
				frameStart = SDL_GetTicks();
				SDL_RenderClear(renderer);
				// Xử lí các thao tác người dùng
				current_time = SDL_GetTicks();
				deltaTime = current_time - start_time;
				start_time = current_time;
				mainMap.Update(deltaTime);
				while (SDL_PollEvent(&event) != 0){
					if (event.type == SDL_QUIT){
						quitGame = true;
						quit = true;
					}
				}
				mainMap.Render();
				SDL_RenderPresent(renderer);
				frameTime = SDL_GetTicks() - frameStart;
				if (frameDelay > frameTime)
					SDL_Delay(frameDelay - frameTime);
			}
		}
	}
	close();
	return 0;
}

bool init(){
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
	return success;
}

void close(){
	// Đóng cửa sổ và renderer
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	window = nullptr;
	renderer = nullptr;
	// Thoát SDL
	Mix_CloseAudio();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}
