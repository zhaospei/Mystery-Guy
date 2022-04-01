#pragma once
#include "Tile.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

bool checkCollision (SDL_Rect a, SDL_Rect b);

bool touchesWall (SDL_Rect box, Tile* tiles[]);