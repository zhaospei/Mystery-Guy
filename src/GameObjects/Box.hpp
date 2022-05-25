#pragma once
#include "Animation.hpp"
#include "Collider.hpp"

class Box: public Texture{
public:
    Box(const std::pair<int, int>& position,bool faceRight);
    ~Box();
    int loot = 0;
    void Update(const Uint32& deltaTime);
    Collider* getCollider();
    void Render();
private:    
    Collider* collider; 
    Animation* animation;
    bool faceRight;
};