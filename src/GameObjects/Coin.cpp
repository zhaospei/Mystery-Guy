#include "Coin.hpp"
#include <iostream>

Coin::Coin(std::pair<int, int> pos){
    animation = new Animation("data/textures/Coin/coin1.png", {6, 1}, 100);
    loadFromFile("data/textures/Coin/coin1.png");
    setSize({27, 27});
    setPosition(pos);
    collider = new Collider(*this);
    eatCoin = false;
    deleteCoin = false;
}

Coin::~Coin(){
    if (animation != nullptr){
        delete animation;
    }
    if (collider != nullptr){
        delete collider;
    }
}

void Coin::Update(const Uint32& deltaTime){
    if (deleteCoin) return;
    if (eatCoin == 1){
        animation = new Animation("data/textures/Coin/coin2.png", {6, 1}, 100);
        loadFromFile("data/textures/Coin/coin2.png");
        setSize({27, 54});
        move({0, -27});
        eatCoin++;
        animation->currentFrame.first = 0;
        animation->setSwitchTime(100);
    }
    if (animation->update(deltaTime) && eatCoin){
        deleteCoin = true;
    }
}

Collider* Coin::getCollider(){
    return collider;
}

void Coin::Render(){
    if (!deleteCoin) render(0, animation->getmBox());
}

