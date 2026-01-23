#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
enum class Direction {
    Left,
    Right,
    Up,
    Down
};

class Player{
    public:
        Player();
        ~Player();
        void Update();
        void Draw();
        void SetPosition(Vector2 pos);
        Vector2 GetPosition();
        void Move();
        void Animate();
        Rectangle GetFrameRec();
        

        


        
    private:
        Direction direction;
        Vector2 position;
        Vector2 speed;
        Texture2D image;
        Rectangle frameRec;
        int animFrame;
        int frameCounter;
        int framesSpeed;
        bool isMoving;
        bool facingLeft;
        float scale;
        


};



#endif