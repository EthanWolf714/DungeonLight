#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
enum class Direction {
    Left,
    Right,
    Up,
    Down
};

enum class  PlayerState {
    Idle,
    Moving
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
        // void HandleInput();
        //void Animate(float dt);
        void AnimateLeftRight();
        void AnimateUpDown();
        Rectangle GetFrameRec();
        

        


        
    private:
        Direction direction;
        PlayerState state;
        Vector2 position;
        Vector2 speed;
        Texture2D image;
        Rectangle frameRec;
        int frameCounter;
        int framesSpeed;
        int currentFrame;
        bool isMoving;
        float direction;
        bool isMovingUp;
        bool isMovingDown;
        float scale;
        int lastDirectionMoved;
        


};



#endif