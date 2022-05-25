#include "Door.hpp"
#include <iostream>

Door::Door(const std::pair<int, int>& position){
    animation = new Animation("data/textures/Door/strange_door.png", {14, 2}, 75);
    loadFromFile("data/textures/Door/strange_door.png");
    setSize({50, 150});
    setPosition(position);
    collider = new Collider(*this);
    open = false;
}

Door::~Door(){
    if (collider != nullptr)
        delete collider;
    if (animation != nullptr)
        delete animation;
}

void Door::Update(const Uint32& deltaTime){
    animation->currentTime += deltaTime;
    if (animation->currentTime >= animation->getSwitchTime()){
        animation->currentTime -= animation->getSwitchTime();
        if (open == true){
            if (animation->currentFrame.second == 1){
                if (animation->currentFrame.first < animation->getFrameCount().first)
                    animation->currentFrame.first++;
            }
            else{
                animation->currentFrame = {0, 1};
            }
        }
        else{
            if (animation->currentFrame.second == 1){
                if (animation->currentFrame.first >= 1)
                    animation->currentFrame.first--;
                else 
                    animation->currentFrame.second = 0;
            }
            else{
                animation->currentFrame.first ++;
                if (animation->currentFrame.first >= 10)
                    animation->currentFrame.first = 0;
            }
        }
    }
    animation->update(false);
}

void Door::Render(){
    render(0, animation->getmBox());
}

Collider* Door::getCollider(){
    return collider;
}
bool Door::checkOpen(){
	return open;
}

void Door::setOpen(const bool& set){
	open = set;
}
