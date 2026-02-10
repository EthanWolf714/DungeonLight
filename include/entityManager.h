#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include "player.h"
#include "torch.h"
#include "vector"
class EntityManager{
    private:
         Player player;
         std::vector<Torch> torches;
         Vector2 playerPos;

    public:
        EntityManager();
        ~EntityManager();
        void Update(float dt);
        void Draw();
        std::vector<Torch> GetTorches();
        Vector2 GetPlayerPos();
        void GetPlayerInput();
        void SetPlayerPos(Vector2 pos);
        void SpawnTorch(Vector2 pos, float restoreAmount);
        void UndoPlayerMovement();
        Rectangle GetPlayerFrameRec();
        Rectangle GetPlayerCollisionRec();
        Rectangle GetPlayerObjRec();
        float GetPlayerLightRadius();
        void UpdatePlayerRects();



};
#endif