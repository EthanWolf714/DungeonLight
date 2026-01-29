#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "raytmx.h"
#include "camera.h"


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
    void HandleCollisions();
    void CreateLightMask();
    Camera2D GetCamera();
    void DrawCollisionDebug();
    float GetPlayerLightRadius();
    

private:

    Player player;
    GameCamera camera;
    TmxMap* map;
    Vector2 spawnPos;
    float dt;
    
    
};

#endif