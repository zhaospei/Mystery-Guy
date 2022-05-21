#pragma once
#include "Texture.hpp"
#include "Collider.hpp"
#include <vector>

class LeverTurn{
public:
    // 0 : close
    // 1 : open
    LeverTurn(const std::pair<int, int>& position);
    ~LeverTurn();
    void addWall(const std::pair<int, int>&  position, int type);
    void Update(const float& deltaTime);
    void Render();
    bool startReStatus();
    float timeSetStatus;
    Texture _switch;
    Collider* colliderSwitch;
    bool status;
    std::vector <std::pair< std::pair<Texture*, Collider*>, int>> walls;
private:
};    