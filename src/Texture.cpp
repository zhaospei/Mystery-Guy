#include <SDL_image.h>
#include <iostream>
#include "Texture.hpp"
#include "Variables.hpp"

Texture::Texture(){
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

Texture::~Texture(){
	free();
}

void Texture::setSize(std::pair<int, int> size){
	mWidth = size.first;
	mHeight = size.second;
	rect.w = size.first;
	rect.h = size.second;
}

void Texture::setPosition(std::pair<int, int> pos){
	rect.x = pos.first;
	rect.y = pos.second;
}

void Texture::move(std::pair<int, int> addpos){
	rect.x += addpos.first;
	rect.y += addpos.second;
}

bool Texture::loadFromRenderedText(std::string textureText, SDL_Color textColor){
	SDL_Surface *textSurface = TTF_RenderText_Solid(fGame, textureText.c_str(), textColor);
	if (textSurface == NULL)
		std::cout << "Khong the tao khong gian ve! SDL_ttf Error: " << TTF_GetError() << std::endl;
	else{
		mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (mTexture == NULL)
			std::cout << "Khong ve duoc chu len man hinh! SDL Error: " << SDL_GetError() << std::endl;
		else{
			mWidth = textSurface->w;
			mHeight = textSurface->h;
			rect.w = mWidth;
			rect.h = mHeight;
		}

		SDL_FreeSurface(textSurface);
	}
	return mTexture != NULL;
}

bool Texture::loadFromFile(std::string path){
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
		std::cout << "Khong the load anh! SDL_image error: " << IMG_GetError() << std::endl;
	else{
		mTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (mTexture == NULL)
			std::cout << "Khong ve duoc anh tai " << path << "! SDL error: " << SDL_GetError() << std::endl;
		else{
			if (!mHeight && !mWidth){
				mWidth = loadedSurface->w;
				mHeight = loadedSurface->h;
			}
		}
		SDL_FreeSurface(loadedSurface);
	}
	return mTexture != NULL;
}

void Texture::free(){
	SDL_DestroyTexture(mTexture);
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

void Texture::render(bool flip, SDL_Rect* clip, double angle, SDL_Point* center){
	if (flip){
		SDL_RenderCopyEx(renderer, mTexture, clip, &rect, angle, center, SDL_FLIP_HORIZONTAL);
	}
	else{
		SDL_RenderCopyEx(renderer, mTexture, clip, &rect, angle, center, SDL_FLIP_NONE);
	} 
}

int Texture::getWidth(){
	return mWidth;
}

int Texture::getHeight(){
	return mHeight;
}

SDL_Rect Texture::getRect() const{
	return rect;
}

std::pair<int, int> Texture::getPosition() const{
	return {rect.x, rect.y};
}

std::pair<int, int> Texture::getSize() const{
	return {rect.w, rect.h};
}
