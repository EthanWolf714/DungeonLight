#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

class Player{
    public:
        Player();
        ~Player();
        void Update();
        void Draw();
        void GetPosition();

        
    private:
        Vector2 position;
        Vector2 speed;
        Texture2D image;
        Rectangle frameRec;
        int frameCounter;
        int framesSpeed;
        int currentFrame;


};



#endif