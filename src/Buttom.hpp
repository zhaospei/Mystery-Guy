#pragma once
#include "Animation.hpp"
#include "Collider.hpp"

class Buttom: public Texture{
public:
    Buttom(const std::pair<int, int>& position);
    ~Buttom();
    void Update();
    void Render();
    int checkCollider(Collider* other, const float& deltaTime);
    Collider* getCollider();
    bool getPressed();
    void setPressed(const bool& set);
private:
    Animation* animation = nullptr;
    Collider* collider = nullptr;
    bool pressed;
};