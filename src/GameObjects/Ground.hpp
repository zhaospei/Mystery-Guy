#pragma once
#include "../GameManager/Texture.hpp"
#include "Collider.hpp"
#include <string>

class Ground: public Texture{
public:
    Ground();
    ~Ground();

    void setGround(const std::string& image, const int& x, const int&y, const int&data);
    Collider* getCollider();

private:
    Collider* collider = nullptr;
};