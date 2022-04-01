#pragma once
#include "RenderWindow.h"
#include "GTexture.h"
#include "Tile.h"
#include "Physical.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Character{
    public:

        static const int CHA_WIDTH = 40;
        static const int CHA_HEIGHT = 40;

        static const int CHA_VEL = 20;

        Character(int p_x = 0, int p_y = 0);
        LTexture gChaTexture;
        // key presses and adjust the dot 
        void handleEvent(SDL_Event& e);

        void move(Tile* tiles[]);

        void setCamera(SDL_Rect& camera);

        void render(SDL_Rect& camera, SDL_Renderer*& gRenderer);

    private:
        //Collision box of Character 
        SDL_Rect mBox;
        //Vel of Character
        int mVelx, mVely;

};