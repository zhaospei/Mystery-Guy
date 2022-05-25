#include "Spikes.hpp"
#include <iostream>

Spikes::Spikes(const std::pair<int, int> position, bool direction){
    this->direction = direction;
    animation = new Animation("data/textures/Spikes/spikes" + std::to_string(direction) + ".png", {2, 1}, 0);
    setSize({50, 50});
    setPosition(position);
    loadFromFile("data/textures/Spikes/spikes" + std::to_string(direction) + ".png");
    collider = new Collider(*this);
}

Spikes::~Spikes(){
    if (animation != nullptr){
        delete animation;
    }
    if (collider != nullptr){
        delete collider;
    }
}
bool Spikes::checkPlayer(Player* player){
    if (direction == 1) return checkTop(player);
    else return checkDown(player);
}

bool Spikes::checkTop(Player* player){
    int Check = collider->checkCollision(player->getCollider());
    if (Check == collider::top || Check == collider::_top){
        return true;
    }
    return false;   
}

bool Spikes::checkDown(Player* player){
    if (player->end) return false;
    if (touchGround){
        int Check = collider->checkCollision(player->getCollider(), 1.0f);
        if (Check == collider::top || Check == collider::_top){
            player->canJump = true;
        }
        return false;
    } 
    if (canDrop == false && abs(getPosition().first - player->getPosition().first) <= 10 
        && ((0 <= player-> getPosition().second - getPosition().second) && player->getPosition().second - getPosition().second <= 200)){
            canDrop = true;
            animation->currentFrame.first = 1;
    }
    int Check = collider->checkCollision(player->getCollider());
    if (Check == collider::down || Check == collider::_down){
        return true;
    }
    return false;
}

void Spikes::Update(const Uint32& deltaTime){
    if (direction == 0 && canDrop && !touchGround){
        velocity.second += (float) deltaTime / 50;
        move(velocity);
    }
    animation->update();
}

void Spikes::Render(){
    render(0, animation->getmBox());
}

Collider* Spikes::getCollider(){
    return collider;
}