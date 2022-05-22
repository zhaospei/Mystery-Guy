#include "Player.hpp"
#include <iostream>
#include <math.h>

Player::Player(std::pair<int, int> positionStart, const bool& faceRightStart){
    animation = new Animation("data/textures/Hero/hero.png", {8, 15}, 100);
    this->positionStart = positionStart;
    this->faceRightStart = faceRightStart;
    setSize({50, 50});
    setPosition(positionStart);
    collider = new Collider(*this);
    body.loadFromFile("data/textures/Hero/hero.png");
    body.setSize({50, 50});
    body.setPosition(getPosition());
    face_Right = faceRightStart;
    animation->currentFrame = {7, 0};
}

Player::~Player(){
    if (collider != nullptr){
        delete collider;
    }
    if (animation != nullptr){
        delete animation;
    }

    for (auto& shadow: shadows){
        delete shadow;
    }
}

void Player::Update(const Uint32& deltaTime){
    oldPosition = getPosition();
    body.setPosition(getPosition());
    if (moveQuick > 0){
        moveQuick--;
        move({20 * (face_Right ? -1 : 1), 0});
        body.setPosition(getPosition());
        createrShadow(face_Right);
    }
    if (canJump) velocity.second = 0;
	velocity.first = 0;
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    if (!moveQuick){
        if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
            velocity.first += speed;
        }
        if (currentKeyStates[SDL_SCANCODE_LEFT]){ 
            velocity.first -= speed;
        }
        if (currentKeyStates[SDL_SCANCODE_SPACE] && canJump) { 
            velocity.second = - sqrt(2.0f * 981.0f * jumHeight);
            canJump = false;
        }
        if (currentKeyStates[SDL_SCANCODE_A] && attack.Check == false){
            attack.Check = true;
            velocity = {0, 0};
            attack.animation->currentFrame = {7, 1};
        }
    }
    if (canJump == false && moveQuick == false){
        velocity.second += 981.0f * deltaTime / 1000;
    }
    if (timeClickS >= 0){
        timeClickS -= deltaTime;
    }
    if (currentKeyStates[SDL_SCANCODE_S] && moveQuick == 0 && timeClickS <= 0){
        moveQuick = 8;
        timeClickS = 1000;
        velocity = {0, 0};
    }
    if (start) attack.Check = false;
    limitPosition();
    updateAnimation(deltaTime);
    updateShadow(deltaTime);
    canJump = false;
    pushStone = false;
    animation->update(0, face_Right);
    if (!start && !end && !attack.Check && !moveQuick){
        move({(int) velocity.first * (int) deltaTime / 1000, (int) velocity.second * (int) deltaTime / 1000});
        body.setPosition(getPosition());
    }
    if (start) attack.Check = false;
}

void Player::updateAnimation(const Uint32& deltaTime){
    if (updateStart(deltaTime)){
       // std::cout << 1 << std::endl;
        return;
    }
    if (updateEnd(deltaTime)){
       // std::cout << 2 << std::endl;
        return;
    }
    if (updatePushStone(deltaTime)) {
       // std::cout << 3 << std::endl;
        return;
    }
    if (updateWinGame(deltaTime)){
       // std::cout << 4 << std::endl;
        return;
    }
    if (updateMoveQuick(deltaTime)){
       // std::cout << 5 << std::endl;
        return;
    }
    if (updateAttack(deltaTime)){
       // std::cout << 6 << std::endl;
        return;
    }
    updateMove(deltaTime);    
}

bool Player::updateStart(const Uint32& deltaTime){
    if (start == false) return false;

    animation->currentTime += deltaTime;
    if (animation->currentTime >= animation->getSwitchTime()){
        animation->currentTime -= animation->getSwitchTime();
        if (animation->currentFrame.second != 0){
            animation->currentFrame = {7, 0};
        }
        else{
            animation->currentFrame.first--;
            if (animation->currentFrame.first == 0){
                start = false;
            }
        }
    }
    animation->update(face_Right);
    return start;
}

void Player::updateShadow(const Uint32& deltaTime) {
	while (!shadows.empty() && shadows.front()->die == true) {
		delete shadows.front();
		shadows.pop_front();
	}
	for (auto& shadow : shadows) {
		shadow->Update(deltaTime);
	}
}

bool Player::updateEnd(const Uint32& deltaTime){
    if (end == false) return false;

    if (animation->update(deltaTime, {7, 0}, face_Right)){
        deletePlayer = true;
    }

    if (deletePlayer == true) Reset();

    return !deletePlayer;
}

bool Player::updateWinGame(const Uint32& deltaTime) {
	if (wingame == false) {
		return false;
	}
	if (animation->update(deltaTime, {7, 0}, face_Right)) {
		deletePlayer = true;
	}
	return !deletePlayer;
}

bool Player::updatePushStone(const float& deltaTime) {
   // std::cout << pushStone << " " << velocity.first << std::endl; 
	if (pushStone == true && velocity.first != 0) {
		animation->update(deltaTime, {6, 2}, face_Right);
        return true;
    }
	return false;
}

bool Player::updateMoveQuick(const float& deltaTime) {
	if (moveQuick == false) {
		return false;
	}
	animation->currentFrame = {3, 8};
	if (velocity.first > 0) face_Right = true;
	if (velocity.first < 0) face_Right = false;
	animation->update(0, face_Right);
	return moveQuick;
}

bool Player::updateAttack(const float& deltaTime){
    if (face_Right)
        attack.setPosition({getPosition().first - 50, getPosition().second});
    else 
        attack.setPosition({getPosition().first + 50, getPosition().second});
    if (attack.Check == false) return false;
    if (animation->update(deltaTime, {4, 3}, face_Right)){
        attack.Check = false;
    }
    attack.animation->update(deltaTime, {3, 14}, face_Right);
    return attack.Check;
}
 

void Player::updateMove(const Uint32& deltaTime){
    if (velocity.first == 0){
        if (canJump){
            animation->update(deltaTime, {4, 5}, face_Right);
        }
        else{
            if (velocity.second < 0){
                animation->update(deltaTime, {3, 7}, face_Right);
            }
            else{
                animation->update(deltaTime, {3, 6}, face_Right);
            }
        }
    }
    else{
        if (velocity.first < 0) face_Right = true;
        else face_Right = false;

        if (canJump){
            animation->update(deltaTime, {6, 1}, face_Right);
        }
        else{
            if (velocity.second < 0){
                animation->update(deltaTime, {3, 7}, face_Right);
            }
            else animation->update(deltaTime, {3, 6}, face_Right);
        }
    }
}

void Player::limitPosition(){
    if (getPosition().first < 0){
        setPosition({0, getPosition().second});
    }

    if (getPosition().first + getSize().first > screenWidth){
        setPosition({screenWidth - getSize().first, getPosition().second});
    }

    if (getPosition().second > screenHeight + 100) {
		end = true;
	}
}
 
void Player::Render(){
    for (auto& shadow: shadows){
        shadow->render(shadow->face_Right);
    }
    body.render(animation->getFlip(), animation->getmBox());

    if (attack.Check){
        attack.Render();
    }
}


void Player::createrShadow(bool faceRight){
    if (moveQuick & 1) {
		Shadow* tmp = new Shadow(true, faceRight);
		tmp->setPosition(oldPosition);
		shadows.push_back(tmp);
	}
	else {
		Shadow* tmp = new Shadow(false, faceRight);
		tmp->setPosition({oldPosition.first - 10, oldPosition.second});
		shadows.push_back(tmp);
	}
}

void Player::Reset(){
    animation->currentFrame = {7, 0};
    start = true;
    end = false;
    deletePlayer = false;
    canJump = false;
    setPosition(positionStart);
    face_Right = faceRightStart;
    _totalHearts--;
}

Collider* Player::getCollider() {
	return collider;
}