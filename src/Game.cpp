#include "Game.hpp"
#include <iostream>

std::string conver(int num){
     num = num * 100;
     int cc = num / 83;
     std::string res = std::to_string(cc);
     cc = num % 83; cc *= 10; cc = cc/ 83;
     res += "." + std::to_string(cc) + "%";
     return res;
}

Game::Game(){
    mainMap = nullptr;
    is_Running = false;
}
Game::~Game(){}

void Game::Init(){
    checkplaysound = false;
    is_Running = true;
    _totalHearts = 3;
    _totalCoins = 0;
    mainMap = new Map();
    mainMap->loadMap("data/map/1.txt");
    TotalCoins_1 = new Texture();
    TotalCoins_1->loadFromFile("data/textures/Background/coins.png");
    TotalCoins_1->setSize({40, 40});
    TotalCoins_1->setPosition({20, 10});
    TotalCoins_2 = new Texture();
    TotalCoins_2->loadFromRenderedText("x0", {255, 255, 255});
    TotalCoins_2->setPosition({70, 10});
    Hearts_1 = new Texture();
    Hearts_1->loadFromFile("data/textures/Background/lifes.png");
    Hearts_1->setSize({40, 40});
    Hearts_1->setPosition({900, 10});
    Hearts_2 = new Texture();
    Hearts_2->loadFromRenderedText("x3", {255, 255, 255});
    Hearts_2->setPosition({940, 10});
    BackGround = new Texture();
    BackGround->loadFromFile("data/textures/Background/background.png");
    BackGround->setPosition({0, 0});
    BackGround->setSize({screenWidth, screenHeight});
    Lose = new Texture();
    Lose->loadFromRenderedText("YOU LOSE!!!", {255, 0, 0});
    Lose->setPosition({410, 100});
    Win = new Texture();
    Win->loadFromRenderedText("YOU WON!!!", {124, 252, 0});
    Win->setPosition({425, 100});
    gamePause = new Texture();
    gamePause->loadFromRenderedText("GAME PAUSED!!!", {255, 255, 255});
    gamePause->setPosition({350, 100});
    std::string fontPath = "data/Fonts/visitor1.ttf";
	fGame = TTF_OpenFont(fontPath.c_str(), 30);
    _next = new Texture();
    _next->loadFromRenderedText("PRESS ENTER TO RETURN MENU!", {131, 111, 255});
    _next->setPosition({300, 300});
    _nextpause = new Texture();
    _nextpause->loadFromRenderedText("PRESS ESC TO CONTINUE OR ENTER TO RETURN MENU!", {131, 111, 255});
    _nextpause->setPosition({100, 300});
    _losemain = new Texture();
    _losemain->loadFromRenderedText("LET'S TRY AGAIN!", {255, 255, 255});
    _losemain->setPosition({400, 200});
    fontPath = "data/Fonts/visitor1.ttf";
	fGame = TTF_OpenFont(fontPath.c_str(), 40);
}

void Game::Update(const Uint32& deltaTime){
    if (LOSEGAME) return;
    if (mainMap->winGame && mainMap->getPlayer()->deletePlayer){
        _curMap++;
        if (_curMap > 5){
            WINGAME = true;
        }
        else{
            delete mainMap;
            std::string _curMapPath = "data/map/" + std::to_string(_curMap) + ".txt";
            mainMap = new Map();
			mainMap->loadMap(_curMapPath);
        }
    }
    mainMap->Update(deltaTime);
    if (_totalHearts <= 0) LOSEGAME = true;
    else{
       Hearts_2->loadFromRenderedText("x" + std::to_string(_totalHearts), {255, 255, 255});
    }
    TotalCoins_2->loadFromRenderedText("x" + std::to_string(_totalCoins), {255, 255, 255});
}

void Game::Render(){
    mainMap->Render();
    TotalCoins_1->render(false);
    TotalCoins_2->render(false);
    Hearts_1->render(false);
    Hearts_2->render(false);
}

void Game::RenderGameOver(){
    Mix_PlayChannel(-1, lose, 0);
    BackGround->render(false);
    Lose->render(false);
    _losemain->render(false);
    _next->render(false);
}

void Game::RenderGameWin(){
    std::string fontPath = "data/Fonts/visitor1.ttf";
	fGame = TTF_OpenFont(fontPath.c_str(), 30);
    Mix_PlayChannel(-1, win, 0);
    _winmain = new Texture();
    std::string winstring = "You have surpassed ";
    winstring += conver(_totalCoins); 
    winstring += " players!";
    _winmain->loadFromRenderedText(winstring, {255, 255, 255});
    _winmain->setPosition({250, 200});
    fontPath = "data/Fonts/visitor1.ttf";
	fGame = TTF_OpenFont(fontPath.c_str(), 40);
    BackGround->render(false);
    Win->render(false);
    _winmain->render(false);
    _next->render(false);
}

void Game::RenderGamePause(){
    BackGround->render(false);
    gamePause->render(false);
    _nextpause->render(false);
}

void Game::Clean(){
    _totalCoins = 0;
    _curMap = 1;
}
