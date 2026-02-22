#ifndef __RELIC_H__
#define __RELIC_H__
#include "raylib.h"
#include <raymath.h>
enum Type {
    WEAPON,
    ITEM,
    WRITING
};
class Relic{
    private:
        enum Type type;
        Vector2 position;
        static Texture2D weaponTexture;
        static Texture2D itemTexture;
        static Texture2D writingTexture;
        bool isCollected;


    public:
        Relic(Vector2 pos, Type type);
        ~Relic();
        void Draw();
        static void LoadSharedTextures();
        static void UnloadSharedTextures();
        Vector2 GetPosition();
        void Collect();
        bool IsCollected();
        bool CheckCollision(Vector2 playerPos, float radius);
        
        


};
#endif // __RELIC_H__