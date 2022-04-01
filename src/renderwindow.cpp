#include "RenderWindow.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

bool initWindow(SDL_Window*& gWindow, SDL_Renderer*& gRenderer){
    bool success = true;

    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")){
	    std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
	}

    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(gWindow == NULL){
        std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else{
        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if(gRenderer == NULL){
            std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        else{
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) & imgFlags)){
                std::cout <<  "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
                success = false;
            }
        }
    }
    return success;
}