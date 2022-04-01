#include "Tile.h"
#include "Physical.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

Tile::Tile( int x, int y, int tileType ){
    mBox.x = x;
    mBox.y = y;

    mBox.w = TILE_WIDTH;
    mBox.h = TILE_HEIGHT;

    mType = tileType;
}

int Tile::getType(){
    return mType;
}

SDL_Rect Tile::getBox(){
    return mBox;
}

