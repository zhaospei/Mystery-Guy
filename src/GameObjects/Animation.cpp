#include <iostream>
#include "Animation.hpp"


Animation::Animation(const std::string& name, std::pair<int, int> frameCount, const Uint32& switchTime){
    loadedSurface = IMG_Load(name.c_str());
	if (loadedSurface == NULL)
		std::cout << "Khong the load anh! SDL_image error: " << IMG_GetError() << std::endl;
    this->frameCount = frameCount;
    this->switchTime = switchTime;
    currentTime = 0;                                
    currentFrame = {0, 0};
    mBox.w = loadedSurface->w / frameCount.first;
    mBox.h = loadedSurface->h / frameCount.second;
}

Animation::~Animation(){
    SDL_FreeSurface(loadedSurface);
}

bool Animation::update(const Uint32& deltaTime, std::pair<int, int> frameLimit, const bool& faceRight){
	bool check = false;
	currentTime += deltaTime;
	if (currentTime >= switchTime) {
		currentTime -= switchTime;
		if (currentFrame.second != frameLimit.second) {
			currentFrame = {0, frameLimit.second};
		}
		else {
			currentFrame.first++;
			if (currentFrame.first >= frameLimit.first) {
				currentFrame.first = 0;
				check = true;
			}
		}
	}
	update(faceRight);
    return check;
}

bool Animation::update(const Uint32& deltaTime, const bool& faceRight){
    return update(deltaTime, std::make_pair(frameCount.first, 0), faceRight);
}

bool Animation::update(const Uint32& deltaTime, std::pair<int, int> frameLimit){
	return update(deltaTime, frameLimit, true);
}

bool Animation::update(const Uint32& deltaTime){
	return update(deltaTime, true);
}

void Animation::update(const bool& faceRight){
	mBox.y = currentFrame.second * mBox.h;
	mBox.x = currentFrame.first * mBox.w;
	if (faceRight){
		flip = 1;
	}
	else{
		flip = 0;
	}
}

void Animation::update(){
	update(true);
}

std::pair<int, int> Animation::getFrameCount(){
	return frameCount;
}

void Animation::setSwitchTime(const Uint32& getSwitchTime){
	this->switchTime = switchTime;
}

Uint32 Animation::getSwitchTime(){
    return switchTime;
}

SDL_Rect* Animation::getmBox(){
	return &mBox;
}

bool Animation::getFlip(){
	return flip;
}

