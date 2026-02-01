#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "raytmx.h"
#include "camera.h"
#include "map.h"
#include "torch.h"

class Game
{
public:
    Game(int screenWidth, int screenHeight);
    ~Game();
    void Draw();
    void Update();
    void HandleInput();
    Vector2 GetPlayerPosition();
    void HandleCollisions();
    void CreateLightMask();
    Camera2D GetCamera();
    void DrawCollisionDebug();
    float GetPlayerLightRadius();
    bool LoadMap(const char* filepath);
    std::vector<Vector2> GetTorchLocations();

private:
    Map currentMap;
    Player player;
    GameCamera camera;
    float dt;
    std::vector<Torch> torches;
};

#endif