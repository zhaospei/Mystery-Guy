#pragma once
#include "Animation.hpp"
#include "Collider.hpp"

class Door: public Texture{
public:
    Door(const std::pair<int, int>& position);
    ~Door();
    void Update(const float &deltaTime);
    void Render();
    Collider* getCollider();
    bool checkOpen();
    void setOpen(const bool& set);
private:
    Animation* animation = nullptr;
    Collider* collider = nullptr;
    bool open;
};