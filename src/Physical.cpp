#include "Physical.h"
#include "RenderWindow.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <algorithm>

bool checkCollision(SDL_Rect a, SDL_Rect b){
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    if(bottomA <= topB) return false;
    if(topA >= bottomB) return false;
    if(rightA <= leftB) return false;
    if(leftA >= rightB) return false;

    return true;
}

int getX(int x){
    if (x % 20 == 0) return x/ 20;
    else return x/ 20 + 1;
}

int getPos(int a, int b){
    return (a - 1) * 294 + b;
}

bool touchesWall(SDL_Rect box, Tile* tiles[]){
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    
    leftA = getX(box.x);
    rightA = getX(box.x + box.w);
    topA = getX(box.y);
    bottomA = getX(box.y + box.h);

    for (int i = std::max(1, topA - 1); i <= std::min(bottomA + 1, TOTAL_TILES_COL); i++)
        for (int j = std::max(1, leftA - 1); j <= std::min(rightA + 1, TOTAL_TILES_ROW); j++){
            int cur = getPos(i, j);
            if ((tiles[cur]->getType() >= TILE_WALL) && (tiles[cur]->getType() <= TILE_WALL)){
                if (checkCollision(box, tiles[cur]->getBox())) return true;
            }
        }
    
    return false;
}