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
        void UndoMovement();
    private:
        Direction direction;
        Vector2 position;
        Vector2 previousPosition;
        float speed;
        Texture2D player_rightLeft;
        Texture2D player_up;
        Texture2D player_down;
        Texture2D* playerSprite;
        Rectangle frameRec;
        int frame;
        float runningTime;
        const int maxFrame {1};
        const float updateTime{.20f};
        static constexpr float frame_width = 16.0f;
        static constexpr float frame_height = 16.0f;
        bool isMoving;
        bool facingLeft;
        float scale;
        
        


};



#endif