#include "Physical.h"
#include "RenderWindow.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

bool checkCollision(SDL_Rect a, SDL_Rect b){
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if(bottomA <= topB) return false;

    if(topA >= bottomB) return false;

    if(rightA <= leftB) return false;

    if(leftA >= rightB) return false;

    return true;
}

bool touchesWall(SDL_Rect box, Tile* tiles[]){
    for(int i = 0; i < TOTAL_TILES; i++){
        if((tiles[i]->getType() >= TILE_WALL) && (tiles[i]->getType() <= TILE_WALL)){
            if(checkCollision(box, tiles[i]->getBox())) return true;
        }
    }
    return false;
}