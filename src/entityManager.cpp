#include "entityManager.h"

EntityManager::EntityManager(){
    Torch::LoadSharedTexture();
}

EntityManager::~EntityManager(){
    Torch::UnloadSharedTexture();
}

void EntityManager::Update(float dt){
    player.Update(dt);
    for(Torch& torch : torches){
        if(torch.CheckCollisions(player.GetPosition(), 16.0f)){
            player.RestoreAmount(torch.GetRestoreAmount());
        }
        

    }
}

void EntityManager::Draw(){
     for(Torch& torch : torches){
            if(!torch.IsConsumed()){
                torch.Draw();
            }
    }
    player.Draw();
}

std::vector<Torch> EntityManager::GetTorches()
{
    return torches;
}

Vector2 EntityManager::GetPlayerPos()
{
    return player.GetPosition();
}

void EntityManager::GetPlayerInput()
{
    player.Move();
    
}

void EntityManager::SetPlayerPos(Vector2 pos)
{
    player.SetPosition(pos);
}

void EntityManager::SpawnTorch(Vector2 pos, float restoreAmount)
{
    torches.emplace_back(pos, restoreAmount);
}

void EntityManager::UndoPlayerMovement(){
    player.UndoMovement();
}

Rectangle EntityManager::GetPlayerFrameRec()
{
    return player.GetFrameRec();
}

Rectangle EntityManager::GetPlayerCollisionRec()
{
    return player.GetCollisionRec();
}

Rectangle EntityManager::GetPlayerInteractRec()
{
    return player.GetInteractRec();
}

float EntityManager::GetPlayerLightRadius()
{
    return player.GetLightRadius();
}

void EntityManager::UpdatePlayerRects()
{
    player.UpdatePlayerRecs();
}