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
       int frame;
       float runningTime;
      const int maxFrame {6};
      Rectangle frameRec;
      const float updateTime{.20f};
      static constexpr float frame_width = 16.0f;
      static constexpr float frame_height = 16.0f;


    public:
     Torch(Vector2 pos, float amount = 0.3f);
     ~Torch();
     void Update(float dt);
     bool CheckCollisions(Vector2 playerPos, float radius);
     bool IsConsumed();
     Vector2 GetPosition();
     void Draw();
     float GetRestoreAmount();
     static void LoadSharedTexture();
     static void UnloadSharedTexture();
     void Animate();
     

};


#endif