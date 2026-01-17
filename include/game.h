#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "raytmx.h"
class Game
{
public:
    Game();
    ~Game();
    void Draw();
    void Update();
    void HandleInput();

private:
    Player player;
};

#endif