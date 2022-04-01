#pragma once
#include <SDL.h>
#include <SDL_image.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int LEVEL_WIDTH = 5880;
const int LEVEL_HEIGHT = 5880;

const int TILE_WIDTH = 20;
const int TILE_HEIGHT = 20;

const int TOTAL_TILES = 90000; // Need Changed
const int TOTAL_TILES_ROW = 294;
const int TOTAL_TILES_COL = 294;

const int TOTAL_TILE_SPRITES = 2;
const int TILE_GROUND = 0;
const int TILE_WALL = 1;


bool initWindow(SDL_Window*& gWindow, SDL_Renderer*& gRenderer);

