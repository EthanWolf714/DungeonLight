#ifndef __KEY_H__
#define __KEY_H__
#include "raylib.h"
#include "raymath.h"
#include "player.h"

class Key{
    private:
       Vector2 position;
       bool collected;
       static Texture2D keySprite;
       Vector2 playerPos;
    
    public:
        Key(Vector2 pos);
        ~Key();
        bool CheckCollisions(Vector2 playerPos, float radius);
        bool IsCollected();
        Vector2 GetPosition();
        void Draw();
        static void LoadSharedTexture();
        static void UnloadSharedTexture();

};
#endif // __KEY_H__