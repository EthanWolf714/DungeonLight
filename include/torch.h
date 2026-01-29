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


    public:
     Torch(Vector2 pos, float amount = 0.3f);
     ~Torch();
     void Update();
     void CheckCollisions(Player& player);
     bool IsConsumed();
     Vector2 GetPosition();

};


#endif