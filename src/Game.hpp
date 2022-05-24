#pragma once
#include "Map.hpp"

std::string conver(int num);

class Game {
public:
    Game();
    ~Game();
    
    void Init();
    void HandleEvents();
    void Update(const Uint32& deltaTime);
    void Render();
    void RenderGameOver();
    void RenderGameWin();
    void RenderGamePause();
    void Clean();
    bool Running() {
        return is_Running;
    }
    bool isLoseGame(){
        return LOSEGAME;
    }
    bool isWinGame(){
        return WINGAME;
    }
    int _curMap = 1;
private:
    bool is_Running;
    Map* mainMap;
    bool checkplaysound = false;
    bool WINGAME = false;
    bool LOSEGAME = false;
    Texture* TotalCoins_1;
    Texture* TotalCoins_2;
    Texture* Hearts_1;
    Texture* Hearts_2;
    Texture* BackGround;
    Texture* Lose;
    Texture* Win;
    Texture* gamePause;
    Texture* _next;
    Texture* _nextpause;
    Texture* _losemain;
    Texture* _winmain;
};