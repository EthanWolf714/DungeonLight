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
    //if consumed return

    //get distance 
    //if distance is less than collision radius
    //restore player light 
    //torch consumed
}

bool Torch::IsConsumed(){
    return consumed;
}

Vector2 Torch::GetPosition(){
    return position;
}