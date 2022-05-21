#include "LeverTurn.hpp"

LeverTurn::LeverTurn(const std::pair<int, int>& position){
    _switch.setSize({50, 50});
    _switch.setPosition(position);
    status = false;
    timeSetStatus = 0.0f;
    colliderSwitch = new Collider(_switch);
}

LeverTurn::~LeverTurn(){
    if (colliderSwitch != nullptr){
        delete colliderSwitch;
    }
    for (auto& wall: walls){
        if (wall.first.first!= nullptr) 
            delete wall.first.first;
        if (wall.first.second != nullptr)
            delete wall.first.second;
    }
}

void LeverTurn::addWall(const std::pair<int, int>&  position, int type){
    walls.push_back({{nullptr, nullptr}, type});
    walls[walls.size() - 1].first.first = new Texture;
    walls[walls.size() - 1].first.second = new Collider(walls[walls.size() - 1].first.first);
    if (type == 1){
        walls[walls.size() - 1].first.first->setSize({100, 50});
    }
    else{
         walls[walls.size() - 1].first.first->setSize({50, 100});
    }
    walls[walls.size() - 1].first.first->setPosition(position);
}

void LeverTurn::Update(const float& deltaTime){
    if (status == false)
        _switch.loadFromFile("data/textures/LeverTurn/lever_turned_left.png");
    else   
        _switch.loadFromFile("data/textures/LeverTurn/lever_turned_right.png");
    if (timeSetStatus > 0.0f){
        timeSetStatus -= deltaTime;
    }
    for (auto& wall: walls){
        if (status){
            wall.first.first->loadFromFile("data/textures/LeverTurn/wood_slab" + std::to_string(wall.second) + "_on.png");
        }
        else{
            wall.first.first->loadFromFile("data/textures/LeverTurn/wood_slab" + std::to_string(wall.second) + "_off.png");
        }
    }
}

void LeverTurn::Render(){
    _switch.render(false);
    for (auto& wall: walls){
        wall.first.first->render(false);
    }
}

bool LeverTurn::startReStatus(){
    return timeSetStatus <= 0.0f;
}