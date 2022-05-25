#pragma once
#include "../GameManager/Variables.hpp"
#include <SDL.h>

class Animation{
public:
    Animation(const std::string& name, std::pair<int, int> frameCount, const Uint32& switchTime);
    ~Animation();
    bool update(const Uint32& deltaTime, std::pair<int, int> frameLimit, const bool& faceRight);
	bool update(const Uint32& deltaTime, const bool& faceRight);
    bool update(const Uint32& deltaTime, std::pair<int, int> frameLimit);
	bool update(const Uint32& deltaTime);
    void update(const bool& faceRight);
    void update();
    Uint32 getSwitchTime();
    void setSwitchTime(const Uint32& getSwitchTime);

    std::pair<int, int> getFrameCount();
    SDL_Rect* getmBox();
    bool getFlip();

    std::pair<int, int> currentFrame;
    Uint32 currentTime;
private:
    std::pair <int, int> frameCount;
    Uint32 switchTime;
    SDL_Surface* loadedSurface;
    SDL_Rect mBox;
    bool flip = 0;
};