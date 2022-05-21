#include "Variables.hpp"

// Giới hạn fps
extern const int FPS;
extern const int frameDelay;
Uint32 frameStart;
unsigned int frameTime;

SDL_Window *window;
int screenWidth = 1000;
int screenHeight = 560;

int GROUND_WIDTH = 50;
int GROUND_HEIGHT = 50;

SDL_Renderer *renderer;

SDL_RendererFlip FLIP_HOR = (SDL_RendererFlip) (SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
SDL_RendererFlip FLIP_NONE = SDL_FLIP_NONE;

TTF_Font *fGame;