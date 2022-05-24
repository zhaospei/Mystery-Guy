#include "Collider.hpp"
#include <iostream>

Collider::Collider(Texture& body) {
    this->body = &body;
}
Collider::Collider(Texture* body) {
    this->body = body;
}

int Collider::checkCollision(Collider* other,float push) {
    std::pair<int, int> otherPosition = other->getPosition();
    std::pair<float, float> otherCenterPosition = other->getCenterPosition();
    std::pair<int, int> otherSize = other->getSize();
    std::pair<int, int> thisPosition = getPosition();
    std::pair<float, float> thisCenterPosition = getCenterPosition();
    std::pair<int, int> thisSize = getSize();
    float deltaX = 2 * otherPosition.first + otherSize.first - 2 * thisPosition.first - thisSize.first;
    float deltaY = 2 * otherPosition.second + otherSize.second - 2 * thisPosition.second - thisSize.second;
    float intersectX = abs(deltaX) - (otherSize.first + thisSize.first);
    float intersectY = abs(deltaY) - (otherSize.second + thisSize.second);
    if (intersectX < 0.0f && intersectY < 0.0f) {
        push = std::min(std::max(push, 0.0f), 1.0f);
        if (intersectX > intersectY) {
            if (deltaX > 0.0f) { 
                if (push == 1.0f) {
                    other->body->setPosition({thisPosition.first + thisSize.first, other->body->getPosition().second});
                    return collider::_right;
                }
                int curMove = intersectX * (1.0f - push);
                Move(curMove, 0.0f);
                other->Move(- intersectX + curMove, 0.0f);
                return collider::right;
            }
            else {
                if (push == 1.0f) {
                    other->body->setPosition({thisPosition.first - otherSize.first, other->body->getPosition().second});
                    return collider::_left;
                }
                int curMove = intersectX * (1.0f - push);
                Move(-curMove, 0.0f);
                other->Move(intersectX - curMove, 0.0f);   
                return collider::left;
            }
        }
        else {
            if (deltaY > 0.0f) {
                if (push == 1.0f) {
                    other->body->setPosition({other->body->getPosition().first, thisPosition.second + thisSize.second});
                    return collider:: _down;
                }
                int curMove = intersectY * (1.0f - push);
                Move(0.0f, curMove);
                other->Move(0.0f, - intersectY + curMove);
                return collider::down;
            }
            else {
                if (push == 1.0f) {
                    other->body->setPosition({other->body->getPosition().first, thisPosition.second - otherSize.second});
                    return collider::_top;
                }
                int curMove = intersectY * (1.0f - push);
                Move(0.0f, - curMove);
                other->Move(0.0f, intersectY - curMove);
                return collider::top;
            }
        }
    }
    if (intersectX <= 0.0f && intersectY <= 0.0f) {
        if (intersectX == 0.0f && intersectY < 0.0f) {
            if (thisCenterPosition.first < otherCenterPosition.first) {
                return collider::_right;
            }
            else {
                return collider::_left;
            }
        }
        if (intersectY == 0.0f && intersectX < 0.0f) {
            if (otherCenterPosition.second < thisCenterPosition.second)
                return collider::_top;
        }
    }
    return 0;
}

int Collider::checkCollision(Collider *other) {
    std::pair<float, float> otherCenterPosition = other->getCenterPosition();
    std::pair<int, int> otherSize = other->getSize();
    std::pair<float, float> thisCenterPosition = getCenterPosition();
    std::pair<int, int> thisSize = getSize();
    float deltaX = otherCenterPosition.first - thisCenterPosition.first;
    float deltaY = otherCenterPosition.second - thisCenterPosition.second;
    int intersectX = 2 * abs(deltaX) - (otherSize.first + thisSize.first);
    int intersectY = 2 * abs(deltaY) - (otherSize.second + thisSize.second);
    if (intersectX < 0 && intersectY < 0) {
        if (intersectX > intersectY) {
            if (deltaX > 0.0f) {
                return collider::right;
            }
            else {
                return collider::left;
            }
        }
        else {
            if (deltaY > 0.0f) {
                return collider::down;
            }
            else {
                return collider::top;
            }
        }
    }
    if (intersectX <= 0 && intersectY <= 0) {
        if (intersectX > intersectY) {
            if (deltaX > 0.0f) {
                return collider::_right;
            }
            else {
                return collider::_left;
            }
        }
        else {
            if (deltaY > 0.0f) {
                return collider::_down;
            }
            else {
                return collider::_top;
            }
        }
    }
    return 0;
}
std::pair<float, float> Collider::getCenterPosition() {
    return {(float) body->getPosition().first + body->getSize().first/2, (float) body->getPosition().second + body->getSize().second/2};
}
std::pair<int, int> Collider::getPosition(){
    return body->getPosition();
}
std::pair<int, int> Collider::getSize() {
    return body->getSize();
}
void Collider::Move(const int& x,const int& y) {
    body->move({x, y});
}