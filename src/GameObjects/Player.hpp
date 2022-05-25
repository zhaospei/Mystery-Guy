#pragma once
#include "Animation.hpp"
#include "Collider.hpp"
#include <string>
#include <list>
#include <iostream>

struct Shadow: public Texture {
	int timeDie = 100;
	bool die = false;
	Shadow(const bool& input, bool faceRight) {
		loadFromFile("data/textures/hero/shadow" + std::to_string(input) + ".png");
		setSize({50, 50});
        face_Right = faceRight;

	}
	void Update(const Uint32& deltaTime) {
		timeDie -= (int) deltaTime;
		if (timeDie <= 0)
			die = true;
	}
	void Render() {
		if (die == false) {
			render();
		}
	}
    bool face_Right = 0;
};


struct Attack: public Texture{
	Collider* collider = nullptr;
	bool Check = false;
    Animation* animation;
	Attack() {
		setSize({50, 50});
		loadFromFile("data/textures/Hero/hero.png");
        animation = new Animation("data/textures/Hero/hero.png", {8, 15}, 200);
		collider = new Collider(*this);
    }
	void Render() {
        render(animation->getFlip(), animation->getmBox());
	}
};

class Player: public Texture{
public: 
    Player(std::pair<int, int> positionStart, const bool& faceRightStart);
    ~Player();
    void Update(const Uint32& deltaTime);
    void Render();
    bool face_Right = false;
    float jumHeight = 180.0f;
    std::pair<int, int> velocity = {0, 0};
    bool start = true;
    bool end = false;
    bool deletePlayer = false;
    bool canJump = false;   
    bool pushStone = false;
    bool wingame = false;
    
    Collider* getCollider();
    Attack attack;
private:
    Texture body;
    Animation* animation;
    float speed = 190.0f;
    int timeClickS = 0;
    int moveQuick = 0;
    std::list<Shadow*> shadows;
    std::pair<float, float> oldPosition;
    std::pair<float, float> positionStart;
    bool faceRightStart;

    Collider* collider = nullptr;
    void createrShadow(bool faceRight);
    void updateAnimation(const Uint32& deltaTime);
    void updateShadow(const Uint32& deltaTime);
    bool updateStart(const Uint32& deltaTime);
    bool updateWinGame(const Uint32& deltaTime);
    bool updateMoveQuick(const Uint32& deltaTime);
    bool updateAttack(const Uint32& deltaTime);
    bool updateEnd(const Uint32& deltaTime);
    void updateMove(const Uint32& deltaTime);
    bool updatePushStone(const Uint32& deltaTime);
    void limitPosition();
    void Reset();
};