#ifndef GAME_H
#define GAME_H
#include "raytmx.h"
#include "camera.h"
#include "map.h"
#include "light.h"
#include "entityManager.h"
#include "text.h"
#include "relic.h"

class Game
{
public:
    Game(int screenWidth, int screenHeight);
    ~Game();
    void Draw();
    void Update();
    bool IsGameOver();
    void HandleInput();
    Vector2 GetPlayerPosition();
    void HandleCollisions();
    void CreateLightMask();
    Camera2D GetCamera();
    void DrawCollisionDebug();
    float GetPlayerLightRadius();
    bool LoadMap(const char *filepath);
    std::vector<Vector2> GetTorchLocations();
    void HandleText();

    // void RenderLight(Light light);

private:
    Map currentMap;
    GameCamera camera;
    float dt;
    EntityManager entityManager;
    Text interactMessage;
    bool dialogOpen;
    Text dialogBox;
    std::string dialogText;
    float coolDown;
    int relics;
    int relicCount;
    bool isGameOver;
};

#endif