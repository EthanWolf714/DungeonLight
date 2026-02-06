#include "torch.h"
//static shared texture
Texture2D Torch::torchSprite = {0};
Torch::Torch(Vector2 pos, float amount)
{
    position = pos;
    consumed = false;
    restoreAmount = amount;
    
}

Torch::~Torch()
{
   
}

void Torch::Draw(){
    DrawTexture(torchSprite, position.x,position.y, WHITE);
}

float Torch::GetRestoreAmount()
{
    return restoreAmount;
}

void Torch::LoadSharedTexture()
{
    torchSprite = LoadTexture("build/assets/Torch.png");
}

void Torch::UnloadSharedTexture()
{
     UnloadTexture(torchSprite);
}


bool Torch::CheckCollisions(Vector2 playerPos, float radius){

    //if torch is not consumed check collisions radius between player and torch
    if(!consumed){
        float dist = Vector2Distance(playerPos, position);
        //TraceLog(LOG_INFO, "Distance to torch: %.2f", dist);
        if(dist < 16.0f){
            //restore light to players light level
            //consume torch
            TraceLog(LOG_INFO, "TORCH CONSUMED!");
            consumed = true;
            return true;
             
        } 
        
    }
  return false;
}

bool Torch::IsConsumed(){
    return consumed;
}

Vector2 Torch::GetPosition(){
    return position;
}