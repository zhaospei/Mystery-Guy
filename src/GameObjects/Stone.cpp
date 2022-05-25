#include "Stone.hpp"

Stone::Stone(const std::pair<int, int>& position){
    body.loadFromFile("data/textures/Stone/stone.png");
    body.setSize({50, 50});
    body.setPosition(position);
    collider = new Collider(body);
    canDrop = true;
}

Stone::~Stone(){
    if (collider != nullptr){
        delete collider;
    }
}

void Stone::Render(){
    body.render(false);
}

void Stone::Update(const Uint32& deltaTime){
    if (canDrop) veclocity.second += 0.01f * (float) deltaTime;
    else veclocity.second = 0;
    body.move(veclocity);
    canDrop = true;
    limitPosition();
}

Collider* Stone::getCollider(){
    return collider;
}

void Stone::limitPosition(){
    if (body.getPosition().first < 0){
        body.setPosition({0, body.getPosition().second});
    }
    if (body.getPosition().first + body.getSize().first > screenWidth){
        body.setPosition({screenWidth - body.getSize().first, body.getPosition().second});
    }
}
