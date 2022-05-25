#include "../GameManager/Variables.hpp"
#include "MainScreen.hpp"

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
    if (GameName != nullptr){
        delete GameName;
    }
    if (currentKeyStates != nullptr){
        delete currentKeyStates;
    }
}

void MainScreen::Init(){
    curState = -1;
    timeClick = 0;
    BackGround = new Texture();
    BackGround->loadFromFile("data/textures/Background/menu_background.png");
    BackGround->setPosition({0, 0});
    BackGround->setSize({screenWidth, screenHeight});
    std::string fontPath = "data/Fonts/GameName.ttf";
	fGame = TTF_OpenFont(fontPath.c_str(), 150);
    GameName = new Texture();
    GameName->loadFromRenderedText("MYSTERY GUY", {255, 255, 255});
    GameName->setPosition({300, 100});
    fontPath = "data/Fonts/visitor1.ttf";
	fGame = TTF_OpenFont(fontPath.c_str(), 40);
    PlayGame = new Texture();
    PlayGame->loadFromRenderedText("PLAY", {255, 255, 255});
    PlayGame->setPosition({50, 350});

    Ins = new Texture();
    Ins->loadFromRenderedText("INSTRUCTION", {255, 255, 255});
    Ins->setPosition({50, 400});

    Exit = new Texture();
    Exit->loadFromRenderedText("EXIT", {255, 255, 255});
    Exit->setPosition({50, 450});
}

int MainScreen::Update(const Uint32& deltaTime){
    currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_DOWN] && timeClick <= 0) {
        curState++;
        Mix_PlayChannel(-1, tick, 0);
        if (curState > 2) curState = 0;
        timeClick = 200;
    }
    currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_UP] && timeClick <= 0) {
        Mix_PlayChannel(-1, tick, 0);
        curState--;
        if (curState < 0) curState = 2;
        timeClick = 200;
    }
    currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_RETURN] && timeClick <= 0) {
        Mix_PlayChannel(-1, tick, 0);
        timeClick = 200;
        return curState;
    }
    if (timeClick >= 0){
        timeClick -= deltaTime;
    }
    PlayGame->loadFromRenderedText("PLAY", {255, 255, 255});
    Ins->loadFromRenderedText("INSTRUCTION", {255, 255, 255});
    Exit->loadFromRenderedText("EXIT", {255, 255, 255});
    PlayGame->setPosition({50, 350});
    Ins->setPosition({50, 400});
    Exit->setPosition({50, 450});

    if (curState == 0){
        PlayGame->loadFromRenderedText(">PLAY", {255, 255, 255});
        PlayGame->setPosition({60, 350});
    }
    else 
        if (curState == 1){
            Ins->loadFromRenderedText(">INSTRUCTION", {255, 255, 255});
           Ins->setPosition({60, 400});
        }
        else {
            if (curState == 2){
                Exit->loadFromRenderedText(">EXIT", {255, 255, 255});
                Exit->setPosition({60, 450});
            }
        }
    return -1;
}

void MainScreen::Render(){
    BackGround->render(false);
    PlayGame->render(false);
    Ins->render(false);
    Exit->render(false);
    GameName->render(false);
}