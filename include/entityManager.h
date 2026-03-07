#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include "player.h"
#include "torch.h"
#include "key.h"
#include "vector"
class EntityManager
{
private:
    Player player;
    std::vector<Torch> torches;
    std::vector<Key> keys;
    Vector2 playerPos;

public:
    EntityManager();
    ~EntityManager();
    void Update(float dt);
    void Draw();
    std::vector<Torch> GetTorches();
    Vector2 GetPlayerPos();
    bool GetPlayerActivity();
    void GetPlayerInput();
    void SetPlayerPos(Vector2 pos);
    void SpawnTorch(Vector2 pos, float restoreAmount);
    void UndoPlayerMovement();
    Rectangle GetPlayerFrameRec();
    Rectangle GetPlayerCollisionRec();
    Rectangle GetPlayerInteractRec();
    float GetPlayerLightRadius();
    int GetPlayerKeyCount();
    void UpdatePlayerRects();
    void SpawnKey(Vector2 pos);
    std::vector<Key> GetKeys();
    void UseKey();
   
   
  
};
#endif