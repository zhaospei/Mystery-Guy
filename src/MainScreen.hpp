#include "Texture.hpp"

class MainScreen{
public:
    MainScreen();
    ~MainScreen();
    
    void Init();
    int Update(const Uint32& deltaTime);
    void Render();
private:
    Texture* GameName;
    Texture* BackGround;
    Texture* PlayGame;
    Texture* Ins;
    Texture* Exit;
    int curState = -1;
    int timeClick;
    const Uint8* currentKeyStates;
};