#pragma once
#include "GTexture.h"
#include "RenderWindow.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Tile{
    public:
		Tile( int x, int y, int tileType);

		int getType();

		SDL_Rect getBox();

    private:
		SDL_Rect mBox;
        
		int mType;
};