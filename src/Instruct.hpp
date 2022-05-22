#include "Texture.hpp"

class Instruct{
public:
    Instruct();
    ~Instruct();
    
    void Init();
    void Render();
private:
    Texture* BackGround;
    Texture* main;
};