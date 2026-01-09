#ifndef GAME_H
#define GAME_H
#include "player.h"
class Game
{
public:
    Game();
    ~Game();
    void Draw();
    void Update();

private:
    Player player;
};

#endif