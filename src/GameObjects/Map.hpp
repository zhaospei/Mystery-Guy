#pragma once
#include "../GameManager/Variables.hpp"
#include "Ground.hpp"
#include "Coin.hpp"
#include "Player.hpp"
#include "Spikes.hpp"
#include "ExitDoor.hpp"
#include "Door.hpp"
#include "Buttom.hpp"
#include "Stone.hpp"
#include "Box.hpp"
#include "Enemies.hpp"
#include "Mushroom.hpp"
#include "LeverTurn.hpp"
#include <string>
#include <vector>

class Map{
public:
    Map();
    ~Map();
    
    void loadMap(std::string path);
    void Render();
    void RenderBackground();
    void RenderGrounds();
    void RenderCoins();
    void RenderPlayer();
    void RenderSpikes();
    void RenderExitDoor();
    void RenderDoor();
    void RenderButtoms();
    void RenderStones();
    void RenderBoxes();
    void RenderEnemies();
    void RenderMushrooms();
    void RenderLeverTurn();
    void Update(const Uint32& deltaTime);
    void UpdateCoins(const Uint32& deltaTime);
    void UpdateSpikes(const Uint32& deltaTime);
    void UpdatePlayer(const Uint32& deltaTime);
    void UpdateDoor(const Uint32& deltaTime);
    void UpdateButtoms(const Uint32& deltaTime);
    void UpdateStones(const Uint32& deltaTime);
    void UpdateBoxes(const Uint32& deltaTime);
    void UpdateEnemies(const Uint32& deltaTime);
    void UpdateMushrooms(const Uint32& deltaTime);
    void UpdateLeverTurn(const Uint32& deltaTime);
    // Colliers:
    void Ground_and_Player(Ground** ground, Player* player, int& width, int& height);
    void Coin_and_Player(std::vector<Coin*>& coins, Player* player);
    void Ground_and_Spikes(Ground** ground, std::list<Spikes*>& spikes, int& width, int& height);
    void ExitDoor_and_Player(ExitDoor* exitdoor, Player* player,bool& wingame);
    void Door_and_Player(Door* door, Player* player);
    void Buttom_and_Stone(std::list<Buttom*>& buttoms, std::list<Stone*>& stones, const Uint32& deltaTime);
    void Buttom_and_Player(std::list<Buttom*>& buttoms, Player* player, const Uint32& deltaTime);
    void Ground_and_Stone(Ground** ground, std::list<Stone*>& stones, int& width, int& height);
    void Spikes_and_Stone(std::list<Spikes*>& spikes, std::list<Stone*>& stones);
    void Stone_and_Player(std::list<Stone*>& stones, Player* player);
    void Stones(std::list<Stone*>& stones);
    void Boxes_and_Player(std::list<Box*>& boxes, Player* player);
    void Enemies_and_Player(std::vector<Enemies*>& enemies, Player* player);
    void MushRoom_and_Player(std::list<Mushroom*>& mushrooms, Player* player);
    void LeverTurn_and_Player(LeverTurn* leverturn, Player* player);
    void LeverTurn_and_Stone(LeverTurn* leverturn, std::list<Stone*>& stones);
    Player* getPlayer();
    bool winGame;
    int exitgame = 0;

private:
    int width, height;
    Ground** grounds;
    Texture* backGround;
    Texture* backGround2;
    bool isBackground2;
    std::vector<Coin*> coins;
    std::vector<Enemies*> enemies;
    std::list<Spikes*> spikes;
    std::list<Buttom*> buttoms;
    std::list<Stone*> stones;
    std::list<Box*> boxes;
    std::list<Mushroom*> mushrooms;
    Player* player;
    ExitDoor* exitdoor;
    Door* door;
    LeverTurn* leverturn;
    
};