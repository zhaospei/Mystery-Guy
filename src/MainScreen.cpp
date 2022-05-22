#include "MainScreen.hpp"
#include "Variables.hpp"
#include <iostream>

MainScreen::MainScreen(){
}
MainScreen::~MainScreen(){
    if (BackGround != nullptr){
        delete BackGround;
    }
    if (PlayGame != nullptr){
        delete PlayGame;
    }
    if (Ins != nullptr){
        delete Ins;
    }
    if (Exit != nullptr){
        delete Exit;
    }
}

void MainScreen::Init(){
    curState = -1;
    timeClick = 0;
    BackGround = new Texture();
    BackGround->loadFromFile("data/textures/Background/background.png");
    BackGround->setPosition({0, 0});
    BackGround->setSize({screenWidth, screenHeight});
    
    PlayGame = new Texture();
    PlayGame->loadFromRenderedText("PLAY", {255, 255, 255});
    PlayGame->setPosition({400, 100});

    Ins = new Texture();
    Ins->loadFromRenderedText("INSTRUCTION", {255, 255, 255});
    Ins->setPosition({400, 200});

    Exit = new Texture();
    Exit->loadFromRenderedText("EXIT", {255, 255, 255});
    Exit->setPosition({400, 300});
}

int MainScreen::Update(const Uint32& deltaTime){
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_DOWN] && timeClick <= 0) {
        curState++;
        if (curState > 2) curState = 0;
        timeClick = 200;
    }
    if (currentKeyStates[SDL_SCANCODE_UP] && timeClick <= 0) {
        curState--;
        if (curState < 0) curState = 2;
        timeClick = 200;
    }
    if (currentKeyStates[SDL_SCANCODE_RETURN] && timeClick <= 0) {
        timeClick = 200;
        return curState;
    }
    if (timeClick >= 0){
        timeClick -= deltaTime;
    }
    PlayGame->loadFromRenderedText("PLAY", {255, 255, 255});
    Ins->loadFromRenderedText("INSTRUCTION", {255, 255, 255});
    Exit->loadFromRenderedText("EXIT", {255, 255, 255});

    if (curState == 0) PlayGame->loadFromRenderedText("PLAY", {0, 255, 255});
    else 
        if (curState == 1) Ins->loadFromRenderedText("INSTRUCTION", {0, 255, 255});
        else 
            if (curState == 2) Exit->loadFromRenderedText("EXIT", {0, 255, 255});
    return -1;
}

void MainScreen::Render(){
    BackGround->render(false);
    PlayGame->render(false);
    Ins->render(false);
    Exit->render(false);
}