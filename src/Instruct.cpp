#include "Instruct.hpp"
#include "Variables.hpp"

Instruct::Instruct(){
}
Instruct::~Instruct(){
    if (BackGround != nullptr){
        delete BackGround;
    }
    if (main != nullptr){
        delete main;
    }
}

void Instruct::Init(){
    BackGround = new Texture();
    BackGround->loadFromFile("data/textures/Background/background.png");
    BackGround->setPosition({0, 0});
    BackGround->setSize({screenWidth, screenHeight});
    
    main = new Texture();
    main->loadFromRenderedText("Instruct", {255, 255, 255});
    main->setPosition({400, 100});
}

void Instruct::Render(){
    BackGround->render(false);
    main->render(false);
}