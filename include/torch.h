#ifndef TORCH_H
#define TORCH_H
#include "raylib.h"
#include "raymath.h"
#include "player.h"
class Torch{
    private:
       Vector2 position;
       bool consumed;
       float restoreAmount;
       static Texture2D torchSprite;
       Vector2 playerPos;
       float radius;


    public:
     Torch(Vector2 pos, float amount = 0.3f);
     ~Torch();
     void Update();
     bool CheckCollisions(Vector2 playerPos, float radius);
     bool IsConsumed();
     Vector2 GetPosition();
     void Draw();
     float GetRestoreAmount();
     static void LoadSharedTexture();
     static void UnloadSharedTexture();

};


#endif