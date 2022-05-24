#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <utility>
#include "Texture.hpp"

const int FPS = 60;
const int frameDelay = 1000 / FPS;
extern Uint32 frameStart;
extern unsigned int frameTime;

extern SDL_Window *window;
extern int screenWidth;
extern int screenHeight;
extern int _totalCoins;
extern int _totalHearts;

extern int GROUND_WIDTH;
extern int GROUND_HEIGHT;

extern SDL_RendererFlip FLIP_HOR;
extern SDL_RendererFlip FLIP_NONE;

extern SDL_Renderer *renderer;

extern TTF_Font *fGame;

//Game Sounds
extern Mix_Chunk *pickCoin;
extern Mix_Chunk *hit;
extern Mix_Chunk *jump;
extern Mix_Chunk *slash;
extern Mix_Chunk *downSound;
extern Mix_Chunk *tick;
extern Mix_Chunk *pushrock;
extern Mix_Chunk *win;
extern Mix_Chunk *lose;
extern Mix_Chunk *kill;
extern Mix_Chunk *landing;
extern Mix_Chunk *mrjump;
extern Mix_Chunk *die;
extern Mix_Chunk *tele;

//Game Music
extern Mix_Music *mainMusic;
extern Mix_Music *mainMenu;