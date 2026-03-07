#include "key.h"
Texture2D Key::keySprite = {0};
Key::Key(Vector2 pos){
    position = pos;
    collected = false;
}

Key::~Key(){
    UnloadSharedTexture();
}

void Key::Draw(){
    DrawTexture(keySprite, position.x,position.y, WHITE);
    
}

void Key::LoadSharedTexture()
{
    keySprite = LoadTexture("build/assets/key.png");
}

void Key::UnloadSharedTexture()
{
    UnloadTexture(keySprite);
}

bool Key::CheckCollisions(Vector2 playerPos, float radius){
    if(!collected){
        float dist = Vector2Distance(playerPos, position);
        //TraceLog(LOG_INFO, "Distance to torch: %.2f", dist);
        if(dist < 16.0f){
            TraceLog(LOG_INFO, "Key Collected!");
            collected = true;
            return true;
             
        } 
        
    }
  return false;
}

bool Key::IsCollected()
{
    return collected;
}

Vector2 Key::GetPosition()
{
    return position;
}