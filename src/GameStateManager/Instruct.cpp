#include "../GameManager/Variables.hpp"
#include "Instruct.hpp"

Instruct::Instruct(){
}
Instruct::~Instruct(){
    if (BackGround != nullptr){
        delete BackGround;
    }
    if (main != nullptr){
        delete main;
    }
    if (title != nullptr){
        delete title;
    }
    if (_next != nullptr){
        delete _next;
    }
}

void Instruct::Init(){
    BackGround = new Texture();
    BackGround->loadFromFile("data/textures/Background/background.png");
    BackGround->setPosition({0, 0});
    BackGround->setSize({screenWidth, screenHeight});
    
    title = new Texture();
    title->loadFromRenderedText("Instruction", {255, 255, 255});
    title->setPosition({400, 20});

    main = new Texture();
    main->loadFromFile("data/textures/Background/tutorial.png");
    main->setPosition({50, 50});
    std::string fontPath = "data/Fonts/visitor1.ttf";
	fGame = TTF_OpenFont(fontPath.c_str(), 30);
    _next = new Texture();
    _next->loadFromRenderedText("PRESS ENTER TO RETURN MENU!", {131, 111, 255});
    _next->setPosition({300, 500});
    fontPath = "data/Fonts/visitor1.ttf";
	fGame = TTF_OpenFont(fontPath.c_str(), 40);
}

void Instruct::Render(){
    BackGround->render(false);
    title->render(false);
    main->render(false);
    _next->render(false);
}