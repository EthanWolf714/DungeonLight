#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "raytmx.h"
class Game
{
public:
    Game(int screenWidth, int screenHeight);
    ~Game();
    void Draw();
    void Update();
    void HandleInput();
    Vector2 GetPlayerPosition();
    bool LoadMap(const char* filepath);
    
    

private:
    Player player;
    Camera2D camera;
    TmxMap* map;
    
};

#endif