#include "../GameManager/Texture.hpp"

class Instruct{
public:
    Instruct();
    ~Instruct();
    
    void Init();
    void Render();
private:
    Texture* BackGround;
    Texture* title;
    Texture* main;
    Texture* _next;
};