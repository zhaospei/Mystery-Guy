#include "Game.hpp"

Game::Game(){
    mainMap = nullptr;
    is_Running = false;
}
Game::~Game(){}

void Game::Init(){
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
    Lose->loadFromRenderedText("YOU LOSE!!!", {255, 255, 255});
    Lose->setPosition({400, 100});
    Win = new Texture();
    Win->loadFromRenderedText("YOU WIN!!!", {255, 255, 255});
    Win->setPosition({400, 100});
    gamePause = new Texture();
    gamePause->loadFromRenderedText("GAME PAUSE!!!", {255, 255, 255});
    gamePause->setPosition({400, 100});
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
    BackGround->render(false);
    Lose->render(false);
}

void Game::RenderGameWin(){
    BackGround->render(false);
    Win->render(false);
}

void Game::RenderGamePause(){
    BackGround->render(false);
    gamePause->render(false);
}

void Game::Clean(){
    _totalCoins = 0;
    _curMap = 1;
}
