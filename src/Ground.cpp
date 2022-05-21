#include "Ground.hpp"
#include "Variables.hpp"

Ground::Ground(){
    collider = nullptr;
}

Ground::~Ground(){
    if (collider != nullptr){
        delete collider;
    }
}

void Ground::setGround(const std::string& image, const int& x, const int&y, const int&data){
    loadFromFile(image);
    setSize({50, 50});
    setPosition({x, y});
    if (data > 0){
        collider = new Collider(*this);
    }
}

Collider* Ground::getCollider() {
	return collider;
}