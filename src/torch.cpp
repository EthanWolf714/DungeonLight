#include "torch.h"
//static shared texture
Texture2D Torch::torchSprite = {0};
Torch::Torch(Vector2 pos, float amount)
{
    position = pos;
    consumed = false;
    restoreAmount = amount;
    frameRec = {0.0f,0.0f,frame_width, frame_height}; 
    runningTime = 0.0f;
    frame = 1;
   
    
}

Torch::~Torch()
{
   
}

void Torch::Update(float dt)
{
    Animate();
}

void Torch::Draw(){
    DrawTextureRec(torchSprite, frameRec,position, WHITE);
}

float Torch::GetRestoreAmount()
{
    return restoreAmount;
}

void Torch::LoadSharedTexture()
{
    torchSprite = LoadTexture("build/assets/torch_spriteSheet.png");
}

void Torch::UnloadSharedTexture()
{
     UnloadTexture(torchSprite);
}

void Torch::Animate()
{
    
    //add animation time to delta
    runningTime += GetFrameTime();

    if (runningTime >= updateTime){
        //move frame
        frame = (frame % 6) + 1;
        //update frame rectangle
        frameRec.x = frame * frame_width;
        //reset animation time
        runningTime = 0.0f;
    }
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