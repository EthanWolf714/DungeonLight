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
    Camera2D GetCamera();
    bool LoadMap(const char* filepath);
    void HandleCollisions();
    void CreateLightMask();
    
    

private:

    Player player;
    Camera2D camera;
    TmxMap* map;
    Vector2 spawnPos;
    float dt;
    
    
};

#endif