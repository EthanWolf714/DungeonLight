#include "entityManager.h"

EntityManager::EntityManager()
{
    Torch::LoadSharedTexture();
    Key::LoadSharedTexture();
}

EntityManager::~EntityManager()
{
    Torch::UnloadSharedTexture();
    Key::UnloadSharedTexture();
}

void EntityManager::Update(float dt)
{
    player.Update(dt);
    
    for (Torch &torch : torches)
    {
        torch.Update(dt);
        if (torch.CheckCollisions(player.GetPosition(), 16.0f))
        {
            player.RestoreAmount(torch.GetRestoreAmount());
        }
    }
    for(Key &key : keys){
        if(key.CheckCollisions(player.GetPosition(), 16.0f)){
            player.CollectKey();
        }
    }

}

void EntityManager::Draw()
{
    for (Torch &torch : torches)
    {
        if (!torch.IsConsumed())
        {
            torch.Draw();
        }
    }
    for(Key &key : keys){
        if(!key.IsCollected()){
            key.Draw();
        }
    }


    player.Draw();
}

std::vector<Torch> EntityManager::GetTorches()
{
    return torches;
}
std::vector<Key> EntityManager::GetKeys(){
    return keys;
}

void EntityManager::UseKey()
{
    player.UseKey();
}

void EntityManager::CleanUpEnititys() 
{
   torches.clear();
   keys.clear();
}
Vector2 EntityManager::GetPlayerPos()
{
    return player.GetPosition();
}

bool EntityManager::GetPlayerActivity()
{
    return player.IsActive();
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


void EntityManager::UndoPlayerMovement()
{
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

int EntityManager::GetPlayerKeyCount()
{
    return player.GetKeys();
}

void EntityManager::UpdatePlayerRects()
{
    player.UpdatePlayerRecs();
}

void EntityManager::SpawnKey(Vector2 pos)
{
    keys.emplace_back(pos);
}

