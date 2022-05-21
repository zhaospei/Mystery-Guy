#include "Animation.hpp"

class Player:public Texture{
public: 
    Player(std::pair<float, float> pos);
    ~Player();
    void Update(const Uint32& deltaTime);
    void Render();
    
    float jumHeight = 180.0f;
    std::pair<float, float> velocity = {0.0f, 0.0f};
    bool start = true;
    bool end = false;
    bool deletePlayer = false;
    bool canJump = false;


private:
    Animation* animation = nullptr;
    float speed = 190.0f;
    float timeClickS = 0.0f;
    int moveQuick = 0;
    std::pair<float, float> oldPosition;
    std::pair<float, float> positionStart;
    void UpdateAnimation(const Uint32& deltaTime);
    void UpdateStart(const Uint32& deltaTime);
    void UpdateEnd(const Uint32& deltaTime);
    void updateMove(const Uint32& deltaTime);
    void limitPosition();
    void reset();
};