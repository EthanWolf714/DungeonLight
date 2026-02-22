#include "entityManager.h"

EntityManager::EntityManager()
{
    Torch::LoadSharedTexture();
}

EntityManager::~EntityManager()
{
    Torch::UnloadSharedTexture();
}

void EntityManager::Update(float dt)
{
    player.Update(dt);
    for (Torch &torch : torches)
    {
        if (torch.CheckCollisions(player.GetPosition(), 16.0f))
        {
            player.RestoreAmount(torch.GetRestoreAmount());
        }
    }
    for (Relic &relic : relics)
    {
        if (!relic.IsCollected() && relic.CheckCollision(player.GetPosition(), 16.0f))
        {
            relic.Collect();
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

    for (Relic &relic : relics)
    {
        if (!relic.IsCollected())
        {
            relic.Draw();
        }
    }

    player.Draw();
}

std::vector<Torch> EntityManager::GetTorches()
{
    return torches;
}

std::vector<Relic> EntityManager::GetRelics()
{
    return relics;
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

void EntityManager::SpawnRelic(Vector2 pos, Type type)
{
    relics.emplace_back(pos, type);
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

void EntityManager::UpdatePlayerRects()
{
    player.UpdatePlayerRecs();
}

void EntityManager::ReserveRelics(int count)
{
    relics.reserve(count);
}
