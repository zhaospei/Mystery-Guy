#pragma once
#include "../GameManager/Texture.hpp"
#include "Collider.hpp"

class ExitDoor: public Texture{
public: 
    ExitDoor(const std::pair<int, int> position);
    ~ExitDoor();
    Collider* getCollider();
    void Render();
private:
    Collider* collider = nullptr; 

};