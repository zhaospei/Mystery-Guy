#include "Buttom.hpp"
#include "iostream"

Buttom::Buttom(const std::pair<int, int>& position){
    animation = new Animation("data/textures/Buttom/buttom_pressed.png", {2, 1}, 100);
    loadFromFile("data/textures/Buttom/buttom_pressed.png");
    setSize({50, 12});
    setPosition(position);
    collider = new Collider(*this);
    pressed = false;
}

Buttom::~Buttom(){
    if (collider != nullptr)
        delete collider;
    if (animation != nullptr)
        delete animation;
}

void Buttom::Update(){
    if (pressed) animation->currentFrame.first = 1;
    else animation->currentFrame.first = 0;
    animation->update(false);
}

void Buttom::Render(){
    render(0, animation->getmBox());
}

int Buttom::checkCollider(Collider* other, const Uint32& deltaTime){
    int Check = collider->checkCollision(other, 1.0f);
    if (Check != 0){
        pressed = true;
    }
    if (Check == collider::_left || Check == collider::_right){
        float tmp = (float) deltaTime / 10.0f;
        other->Move(tmp, 0.0f);
        other->body->setPosition({other->getPosition().first, getPosition().second - other->getSize().second});
    }
    return Check;

}

Collider* Buttom::getCollider(){
    return collider;
}

bool Buttom::getPressed(){
    return pressed;
}
void Buttom::setPressed(const bool& set){
    pressed = set;
}
