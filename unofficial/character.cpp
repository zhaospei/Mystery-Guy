#include "Character.h"
#include "Physical.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

Character::Character(){
    mBox.x = 0;
    mBox.y = 0;
    mBox.w = CHA_WIDTH;
    mBox.h = CHA_HEIGHT;

    mVelx = 0;
    mVely = 0;
}

void Character::handleEvent(SDL_Event& e){
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
        switch( e.key.keysym.sym ){
            case SDLK_w: mVely -= CHA_VEL; break;
            case SDLK_s: mVely += CHA_VEL; break;
            case SDLK_a: mVelx -= CHA_VEL; break;
            case SDLK_d: mVelx += CHA_VEL; break;
        }
    }
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 ){
        switch( e.key.keysym.sym ){
            case SDLK_w: mVely += CHA_VEL; break;
            case SDLK_s: mVely -= CHA_VEL; break;
            case SDLK_a: mVelx += CHA_VEL; break;
            case SDLK_d: mVelx -= CHA_VEL; break;
        }
    }
}

void Character::move(Tile *tiles[]){
    mBox.x += mVelx;

    if( ( mBox.x < 0 ) || ( mBox.x + CHA_WIDTH > LEVEL_WIDTH ) || touchesWall( mBox, tiles ) ){
        mBox.x -= mVelx;
    }

    mBox.y += mVely;
    
    if( ( mBox.y < 0 ) || ( mBox.y + CHA_HEIGHT > LEVEL_HEIGHT ) || touchesWall( mBox, tiles ) ){
        mBox.y -= mVely;
    }
}

void Character::setCamera(SDL_Rect& camera){
	camera.x = (mBox.x + CHA_WIDTH / 2) - SCREEN_WIDTH / 2;
	camera.y = (mBox.y + CHA_HEIGHT / 2) - SCREEN_HEIGHT / 2;
    if (camera.x < 0) camera.x = 0;
    if (camera.y < 0) camera.y = 0;
    if (camera.x + camera.w > LEVEL_WIDTH) camera.x = LEVEL_WIDTH - camera.w;
    if (camera.y + camera.h > LEVEL_HEIGHT) camera.y = LEVEL_HEIGHT - camera.h;
}

void Character::render(SDL_Rect& camera){
	gChaTexture.render(mBox.x - camera.x, mBox.y - camera.y);
}