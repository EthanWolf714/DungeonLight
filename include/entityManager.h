#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include "player.h"
#include "torch.h"
#include "relic.h"
#include "vector"
class EntityManager
{
private:
    Player player;
    std::vector<Torch> torches;
    std::vector<Relic> relics;
    Vector2 playerPos;

public:
    EntityManager();
    ~EntityManager();
    void Update(float dt);
    void Draw();
    std::vector<Torch> GetTorches();
    std::vector<Relic> GetRelics();
    Vector2 GetPlayerPos();
    bool GetPlayerActivity();
    void GetPlayerInput();
    void SetPlayerPos(Vector2 pos);
    void SpawnTorch(Vector2 pos, float restoreAmount);
    void SpawnRelic(Vector2 pos, Type type);
    void UndoPlayerMovement();
    Rectangle GetPlayerFrameRec();
    Rectangle GetPlayerCollisionRec();
    Rectangle GetPlayerInteractRec();
    float GetPlayerLightRadius();
    void UpdatePlayerRects();
    void ReserveRelics(int count);
   
  
};
#endif