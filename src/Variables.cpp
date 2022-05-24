#include "Variables.hpp"

// Giới hạn fps
extern const int FPS;
extern const int frameDelay;
Uint32 frameStart;
unsigned int frameTime;

SDL_Window *window;
int _totalCoins = 0;
int _totalHearts = 0;

int screenWidth = 1000;
int screenHeight = 560;

int GROUND_WIDTH = 50;
int GROUND_HEIGHT = 50;

SDL_Renderer *renderer;

SDL_RendererFlip FLIP_HOR = (SDL_RendererFlip) (SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
SDL_RendererFlip FLIP_NONE = SDL_FLIP_NONE;

TTF_Font *fGame;

// Game Sounds

Mix_Chunk *pickCoin;
Mix_Chunk *hit;
Mix_Chunk *jump;
Mix_Chunk *slash;
Mix_Chunk *downSound;
Mix_Chunk *tick;
Mix_Chunk *pushrock;
Mix_Chunk *win;
Mix_Chunk *lose;
Mix_Chunk *kill;
Mix_Chunk *landing;
Mix_Chunk *mrjump;
Mix_Chunk *die;
Mix_Chunk *tele;

//Game Musics
Mix_Music *mainMusic;
Mix_Music *mainMenu;