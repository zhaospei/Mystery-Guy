#include "ExitDoor.hpp"

ExitDoor::ExitDoor(const std::pair<int, int> position){
    loadFromFile("data/textures/ExitDoor/door.png");
    setSize({75, 75});
    setPosition(position);
    collider = new Collider(*this);
}

ExitDoor::~ExitDoor(){
    if (collider != nullptr)
        delete collider;
}

void ExitDoor::Render(){
    render();
}

Collider* ExitDoor::getCollider(){
    return collider;
}