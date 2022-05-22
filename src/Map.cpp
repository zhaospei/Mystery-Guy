#include "Map.hpp"
#include "Variables.hpp"

#include <fstream>
#include <string>
#include <iostream>
#include <math.h>

Map::Map(){
    winGame = false;
    grounds = nullptr;
    exitdoor = nullptr;
    door = nullptr;
    player = nullptr;
    leverturn = nullptr;
    isBackground2 = 0;
    width = 12, height = 20;
    grounds = new Ground * [width];
	for (int i = 0; i < width; i++) {
		grounds[i] = new Ground[height];
	}
}

Map::~Map(){
    width = 0, height = 0;
    isBackground2 = 0;
    for (int i = 0; i < width; i++) {
		delete[] grounds[i];
	}
    for (auto& coin : coins) {
		delete coin;
	}
    for (auto& spike : spikes) {
		delete spike;
	}
    for (auto& buttom: buttoms){
        delete buttom;
    }
    for (auto& stone: stones){
        delete stone;
    }
    for (auto& box: boxes){
        delete box;
    }
    for (auto& enemie: enemies){
        delete enemie;
    }
    if (grounds != nullptr) {
		delete grounds;
	}
    if (player != nullptr){
        delete player;
    }
    if (exitdoor != nullptr) {
		delete exitdoor;
	}
    if (door != nullptr){
        delete door;
    }
    if (leverturn != nullptr){
        delete leverturn;
    }
    if (backGround != nullptr){
        delete backGround;
    }
    if (backGround2 != nullptr){
        delete backGround2;
    }
}

void Map::loadMap(std::string path){
    backGround = new Texture();
    backGround2 = new Texture();
    backGround->loadFromFile("data/textures/background/background.png");
    if (isBackground2) backGround2->loadFromFile("data/textures/background/bg_2.png");
    backGround->setPosition({0, 0});
    backGround->setSize({1000, 560});
    backGround2->setSize({1000, 560});
    backGround2->setPosition({0, 0});
	std::ifstream map(path.c_str());	
	if (map.fail()){
		std::cout << "Khong the mo file Map!" << std::endl;
		return ;
	}
    std::string base = "data/textures/ground/";
	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
			int typeGround = 0;
            map >> typeGround; 
            if (typeGround == 0) continue;
            std::string cur = base + std::to_string(typeGround);
            cur += ".png";
            if (typeGround < -9 || typeGround > 18) std::cout << "Map chua thong so khong hop le" << std::endl;            
            grounds[i][j].setGround(cur, j * GROUND_WIDTH, i * GROUND_WIDTH, typeGround);
        }
	}
    map >> isBackground2;
    int totalCoins;
    map >> totalCoins;
    for (int i = 0; i < totalCoins; i++){
        int x, y;
        map >> x >> y;
        coins.push_back(new Coin({x - 13.5, y - 13.5}));
    }

    int x, y, _type;
    map >> x >> y >> _type;
    player = new Player({x, y}, _type);
    int tolCur = 0;
    map >> tolCur; bool _ntype;
    for (int i = 0; i < tolCur; i++){
        map >> x >> y >> _ntype;
        spikes.push_back(new Spikes({x, y}, _ntype));
    }
    map >> x >> y;
    exitdoor = new ExitDoor({x, y});

    map >> x >> y;
    door = new Door({x, y});

    map >> tolCur;
    for (int i = 0; i < tolCur; i++){
        map >> x >> y;
        buttoms.push_back(new Buttom({x, y}));
    }

    map >> tolCur;
    for (int i = 0; i < tolCur; i++){
        map >> x >> y;
        stones.push_back(new Stone({x, y}));
    }    

    map >> tolCur;
    for (int i = 0; i < tolCur; i++){
        bool type = 0;
        map >> x >> y >> type;
        boxes.push_back(new Box({x, y}, type));
    }
    std::pair<int, int> _pos, _start, _end; 
    map >> tolCur;
    for (int i = 0; i < tolCur; i++){
        map >> _type >> _pos.first >> _pos.second >> _start.first >> _start.second >> _end.first >> _end.second;
        enemies.push_back(new Enemies(_type, _pos, _start, _end));
    }

    map >> tolCur;
    for (int i = 0; i < tolCur; i++){
        map >> x >> y;
        mushrooms.push_back(new Mushroom({x, y}));
    }
    map >> tolCur;
    for (int i = 0; i < tolCur; i++){
        map >> x >> y;
        leverturn = new LeverTurn({x, y});
        int _tolcur = 0;
        map >> _tolcur;
        for (int j = 0; j < _tolcur; j++){
            map >> x >> y >> _ntype;
            leverturn->addWall({x, y}, _ntype);
        }
    }
	map.close();
}

void Map::Render(){
    RenderBackground();
    RenderDoor();
    RenderLeverTurn();
    RenderGrounds();
    RenderCoins();
    RenderSpikes();
    RenderExitDoor();
    RenderButtoms();
    RenderBoxes();
    RenderStones();
    RenderPlayer();
    RenderEnemies();
    RenderMushrooms();
}

void Map::RenderBackground(){
    backGround->render(false);
    if (isBackground2) backGround2->render(false);
}
void Map::RenderGrounds(){
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            grounds[i][j].render();
        }
    }
}

void Map::RenderCoins(){
    for (auto& coin: coins){
        coin->Render();
    }
}

void Map::RenderPlayer(){
    if (player->deletePlayer == false) player->Render();
}

void Map::RenderSpikes(){
    for (auto& spike: spikes){
        spike->Render();
    }
}

void Map::RenderBoxes(){
    for (auto& box: boxes){
        box->Render();
    }
}

void Map::RenderExitDoor(){
    exitdoor->Render();
}

void Map::RenderDoor(){
    door->Render();
}

void Map::RenderButtoms(){
    for (auto& buttom: buttoms){
        buttom->Render();
    }
}

void Map::RenderStones(){
    for (auto& stone: stones){
        stone->Render();
    }
}

void Map::RenderEnemies(){
    for (auto& enemie: enemies){
        if (enemie->deleteBot == false) enemie->Render(); 
    }
}

void Map::RenderMushrooms(){
    for (auto& mushroom: mushrooms){
        mushroom->Render();
    }
}

void Map::RenderLeverTurn(){
    if (leverturn != nullptr) leverturn->Render();
}

void Map::Update(const Uint32& deltaTime){
    Coin_and_Player(coins, player);
    Ground_and_Spikes(grounds, spikes, width, height);
    Door_and_Player(door, player);
    ExitDoor_and_Player(exitdoor, player, winGame);
    Ground_and_Player(grounds, player, width, height);
    Ground_and_Stone(grounds, stones, width, height);
    Spikes_and_Stone(spikes, stones);
    Stone_and_Player(stones, player);
    Boxes_and_Player(boxes, player);
    Enemies_and_Player(enemies, player);
    MushRoom_and_Player(mushrooms, player);
    LeverTurn_and_Player(leverturn, player);
    LeverTurn_and_Stone(leverturn, stones);
    Stones(stones);
    UpdateCoins(deltaTime);
    UpdatePlayer(deltaTime);
    UpdateSpikes(deltaTime);
    UpdateDoor(deltaTime);
    UpdateButtoms(deltaTime);
    UpdateStones(deltaTime);
    UpdateBoxes(deltaTime);
    UpdateEnemies(deltaTime);
    UpdateMushrooms(deltaTime);
    UpdateLeverTurn(deltaTime);
}

void Map::UpdateCoins(const Uint32& deltaTime){
    for (int i = 0; i < (int) (coins.size()); i++){
        coins[i]->Update(deltaTime);
    }
}

void Map::UpdateSpikes(const Uint32& deltaTime){
    for (auto& spike : spikes) {
		if (spike->checkPlayer(player)) {
			player->end = true;
		}
		spike->Update(deltaTime);
	}
}

void Map::UpdatePlayer(const Uint32& deltaTime){
    if (player->deletePlayer){
        if (player->wingame) exitgame = 1;
		else {
            exitgame = 2;
        }
        return;
    }
    player->Update(deltaTime);
}

void Map::UpdateDoor(const Uint32& deltaTime){
    door->Update(deltaTime);
}

void Map::UpdateButtoms(const Uint32& deltaTime){
    door->setOpen(false);
    for (auto& buttom: buttoms){
        buttom->setPressed(false);
    }
    Buttom_and_Stone(buttoms, stones, deltaTime);
    Buttom_and_Player(buttoms, player, deltaTime);
    if (!buttoms.empty()) door->setOpen(true);
    for (auto& buttom: buttoms){
        buttom->Update();
        if (!buttom->getPressed()){
            door->setOpen(false);
        }
    }
}

void Map::UpdateStones(const Uint32& deltaTime) {
	for (auto& stone : stones) {
		stone->Update(deltaTime);
	}
}

void Map::UpdateBoxes(const Uint32& deltaTime){
    for (auto& box: boxes){
        box->Update(deltaTime);
    }
}

void Map::UpdateEnemies(const Uint32& deltaTime){
    for (int i = 0; i < enemies.size(); i++){
        if (enemies[i]->deleteBot){
            delete enemies[i];
            enemies.erase(enemies.begin() + i);
            i--;
        }
        else{
            enemies[i]->Update(deltaTime);
        }
    }
}

void Map::UpdateMushrooms(const Uint32& deltaTime){
    for (auto& mushroom: mushrooms){
        mushroom->Update(deltaTime);
    }
}

void Map::UpdateLeverTurn(const Uint32& deltaTime){
    if (leverturn != nullptr) leverturn->Update(deltaTime);
}

Player* Map::getPlayer(){
    return player;
}

//Colliders:
void Map::Ground_and_Player(Ground** ground, Player* player, int& width, int& height) {
	if (player == nullptr) {
		return;
	}
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (ground[i][j].getCollider() == nullptr) continue;
			else { 
				int Check = ground[i][j].getCollider()->checkCollision(player->getCollider(), 1.0f);
				if (Check == collider::top || Check == collider::_top) {
					player->canJump = true;
				}
				if (Check == collider::down || Check == collider::_down) {
					player->velocity.second *= 0.8f;
				}
			}
		}
	}
}

void Map::Coin_and_Player(std::vector<Coin*>& coins, Player* player) {
	if (player == nullptr) {
		return;
	}
	for (auto& coin : coins) {
		if (coin->getCollider()->checkCollision(player->getCollider())) {
			coin->eatCoin++;
            if (coin->eatCoin == 1) _totalCoins ++;
		}
	}
}

void Map::Ground_and_Spikes(Ground** ground, std::list<Spikes*>& spikes, int& width, int& height) {
	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
			if (ground[i][j].getCollider() == nullptr) continue;
			else {
				for (auto& spike : spikes) {
					int Check = ground[i][j].getCollider()->checkCollision(spike->getCollider(), 1.0f);
					if (Check == collider::top || Check == collider::_top) {
						spike->canDrop = false;
						spike->touchGround = true;
					}
				}
			}
		}
	}
}

void Map::ExitDoor_and_Player(ExitDoor* exitdoor, Player* player,bool& wingame) {
	if (exitdoor->getCollider()->checkCollision(player->getCollider())) {
		player->setPosition({exitdoor->getPosition().first + 12.5, exitdoor->getPosition().second + 12.5});
		player->wingame = true;
        winGame = true;
	}
}

void Map::Door_and_Player(Door* door, Player* player) {
	if (door == nullptr || player == nullptr) {
		return;
	}
	if (door->checkOpen() == false){
		door->getCollider()->checkCollision(player->getCollider(), 1.0f);
	}
}

void Map::Buttom_and_Stone(std::list<Buttom*>& buttoms, std::list<Stone*>& stones, const float& deltaTime) {
	for (auto& buttom : buttoms) {
		for (auto& stone : stones) {
			int Check = buttom->checkCollider(stone->getCollider(), deltaTime);
			if (Check == collider::top || Check == collider::_top) {
				stone->canDrop = false;
			}
		}
	}
}

void Map::Buttom_and_Player(std::list<Buttom*>& buttoms, Player* player, const float& deltaTime) {
	if (player == nullptr) {
		return;
	}
	for (auto& buttom : buttoms) {
		int Check = buttom->checkCollider(player->getCollider(), deltaTime);
		if (Check == collider::top || Check == collider::_top) {
			player->canJump = true;
		}
	}
}

void Map::Ground_and_Stone(Ground** ground, std::list<Stone*>& stones, int& width, int& height){
    for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
			if (ground[i][j].getCollider() == nullptr) continue;
			else{
				for (auto& stone : stones){
					int Check = ground[i][j].getCollider()->checkCollision(stone->getCollider(), 1.0f);
					if (Check == collider::top || Check == collider::_top){
						stone->canDrop = false;
					}
				}
			}
		}
	}
}
void Map::Spikes_and_Stone(std::list<Spikes*>& spikes, std::list<Stone*>& stones){
    for (auto& spike : spikes){
		for (auto& stone : stones){
			int Check = spike->getCollider()->checkCollision(stone->getCollider(), 1.0f);
			if (Check == collider::top || Check == collider::_top){
				stone->canDrop = false;
			}
		}
	}
}
void Map::Stone_and_Player(std::list<Stone*>& stones, Player* player){
    if (player == nullptr){
		return;
	}
	for (auto& stone : stones){
		int Check = stone->getCollider()->checkCollision(player->getCollider(), 0.5f);
        
		if (Check == collider::_top || Check == collider::top) {
			player->canJump = true;
		}
		if (Check == collider::left || Check == collider::_left || Check == collider::right || Check == collider::_right) {
	    	player->pushStone = true;
		}
	}
}
void Map::Stones(std::list<Stone*>& stones){
    for (auto& stone1 : stones) {
		for (auto& stone2 : stones) {
			if (stone1 == stone2) {
				continue;
			}
			int Check = stone1->getCollider()->checkCollision(stone2->getCollider());
			int Check1 = stone2->getCollider()->checkCollision(stone1->getCollider());
			if (Check == collider::top || Check == collider::_top ) {
				stone2->body.setPosition({stone1->body.getPosition().first, stone1->body.getPosition().second - stone2->body.getSize().second});
				stone2->canDrop = false;
			}
			else if ( Check1 == collider::top || Check1 == collider::_top) {
				stone1->body.setPosition({stone2->body.getPosition().first, stone2->body.getPosition().second - stone1->body.getSize().second});
				stone1->canDrop = false;
			}
			else {
				stone2->getCollider()->checkCollision(stone1->getCollider(), 0.6f);
				stone1->getCollider()->checkCollision(stone2->getCollider(), 0.6f);
			}
		}
	}
}

void Map::Boxes_and_Player(std::list<Box*>& boxes, Player* player) {
	if (player == nullptr) return;
	for (auto& box : boxes) {
		if (player->attack.Check == true){
			if (box->loot == 0 && player->attack.collider->checkCollision(box->getCollider())){
				box->loot++;
                _totalCoins += 5;
			}
		}
	}
}
void Map::Enemies_and_Player(std::vector<Enemies*>& enemies, Player* player){
    if (player == nullptr) {
		return;
	}
	for (auto& enemie : enemies) {
		if (player->attack.Check && enemie->checkDie == 0) {
			int Check = player->attack.collider->checkCollision(enemie->getCollider());
			if (Check != 0 && Check != collider::_top && Check != collider::_down) {
				enemie->checkDie++;
			}
		}
		else if (player->end == false && enemie->checkDie == 0 && enemie->getCollider()->checkCollision(player->getCollider()) == collider::top) {
			enemie->checkDie++;
		}
		else if (enemie->checkDie == 0 ) {
			int Check = enemie->getCollider()->checkCollision(player->getCollider());
			if (Check == collider::right || Check == collider::left) {
				player->end = true;
                player->attack.Check = false;
			}
		}
	}
}

void Map::MushRoom_and_Player(std::list<Mushroom*>& mushrooms, Player* player){
    if (player == nullptr){
        return;
    }
    for (auto& mushroom : mushrooms) {
		int Check = mushroom->getCollider()->checkCollision(player->getCollider(), 1.0f);
		if (Check != 0 && Check != collider::down && Check != collider::_down) {
			player->velocity.second= -sqrt(2.0f * 981.0f * player->jumHeight * 1.7f);
			player->canJump = false;
		}
	}
}

void Map::LeverTurn_and_Player(LeverTurn* leverturn, Player* player){
    if (player == nullptr || leverturn == nullptr)
		return;
	if (player->attack.Check == true && leverturn->startReStatus()){
		if (leverturn->colliderSwitch->checkCollision(player->attack.collider) != 0){
			leverturn->status = !(leverturn->status);
			leverturn->timeSetStatus = 500;
		}
	}
	if (leverturn->status == false ) {
		for (auto &wall: leverturn->walls){
			int Check = wall.first.second->checkCollision(player->getCollider(), 1.0f);
			if ( Check == collider::top || Check == collider::_top){
				player->canJump = true;
			}
		}
	}
}
void Map::LeverTurn_and_Stone(LeverTurn* leverturn, std::list<Stone*>& stones){
    if (leverturn == nullptr){
		return;
	}
	for (auto& stone : stones){
		for (auto wall: leverturn->walls){
			if (leverturn->status == false){
				int Check = wall.first.second->checkCollision(stone->getCollider(), 1.0f);
				if (Check == collider::top || Check == collider::_top){
					stone->canDrop = false;
				}
			}
		}
	}
}