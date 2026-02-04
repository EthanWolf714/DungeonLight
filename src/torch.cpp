#include "torch.h"

Torch::Torch(Vector2 pos, float amount)
{
    position = pos;
    consumed = false;
    restoreAmount = amount;
    torchSprite = LoadTexture("build/assets/Torch.png");
}

Torch::~Torch()
{
    UnloadTexture(torchSprite);
}

void Torch::Draw(){
    DrawTexture(torchSprite, position.x,position.y, WHITE);
}


void Torch::CheckCollisions(Player& player){

    //if torch is not consumed check collisions radius between player and torch
    if(!consumed){
        float dist = Vector2Distance(player.GetPosition(), position);
        //TraceLog(LOG_INFO, "Distance to torch: %.2f", dist);
        if(dist < 16.0f){
            //restore light to players light level
            //consume torch
            player.RestoreAmount(restoreAmount);
            TraceLog(LOG_INFO, "TORCH CONSUMED!");
            consumed = true;
             
        } 
    }
  
}

bool Torch::IsConsumed(){
    return consumed;
}

Vector2 Torch::GetPosition(){
    return position;
}