#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <utility>
#include "Texture.hpp"

const int FPS = 60;
const int frameDelay = 1000 / FPS;
extern Uint32 frameStart;
extern unsigned int frameTime;

extern SDL_Window *window;
extern int screenWidth;
extern int screenHeight;

extern int GROUND_WIDTH;
extern int GROUND_HEIGHT;

extern SDL_RendererFlip FLIP_HOR;
extern SDL_RendererFlip FLIP_NONE;

extern SDL_Renderer *renderer;

extern TTF_Font *fGame;