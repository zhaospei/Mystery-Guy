#pragma once
#include "Variables.hpp"
#include "Texture.hpp"

enum collider {
    top = 8, right = 6, left = 4, down = 2,
    _top = -8, _right = -6, _left = -4, _down = -2,
};

class Collider {
public:
    Collider(Texture& body);
	Collider(Texture* body);
    ~Collider(){

    }
    int checkCollision(Collider* other, float push);
    int checkCollision(Collider* other);
    std::pair<float, float> getCenterPosition();
    std::pair<int, int> getPosition();
    std::pair<int, int> getSize();
    void Move(const int& x , const int& y);
    Texture* body;
};

