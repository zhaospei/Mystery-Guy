#pragma once
#include "Animation.hpp"
#include "Collider.hpp"
class Coin:public Texture{
public: 
    Coin(std::pair<int, int> pos);
    ~Coin();
    void Update(const Uint32& deltaTime);
    void Render();
    Collider* getCollider();
    bool deleteCoin;
    int eatCoin;
private:
    Animation* animation = nullptr;
    Collider* collider = nullptr;
};