#include "relic.h"

Texture2D Relic::weaponTexture = {0};
Texture2D Relic::itemTexture = {0};
Texture2D Relic::writingTexture = {0};

Relic::Relic(Vector2 pos, Type type)
{
    isCollected = false;
    position = pos;
    this->type = type;

    weaponTexture = LoadTexture("build/assets/relic_sword.png");
    itemTexture = LoadTexture("build/assets/relic_item.png");
    writingTexture = LoadTexture("build/assets/relic_writing.png");
}

Relic::~Relic()
{
   
}

void Relic::Draw()
{
    if (isCollected) return;
    
    switch(type)
    {
        case WEAPON: DrawTexture(weaponTexture, position.x, position.y, WHITE); break;
        case ITEM: DrawTexture(itemTexture, position.x, position.y, WHITE); break;
        case WRITING: DrawTexture(writingTexture, position.x, position.y, WHITE); break;
    }
} 

void Relic::LoadSharedTextures()
{
    
} 

Vector2 Relic::GetPosition()
{
    return position;
}

void Relic::Collect()
{
    isCollected = true;
}

bool Relic::IsCollected()
{
    return isCollected;
}

bool Relic::CheckCollision(Vector2 playerPos, float radius)
{
    return CheckCollisionPointCircle(position, playerPos, radius);
}






