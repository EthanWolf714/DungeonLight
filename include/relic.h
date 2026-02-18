#ifndef __RELIC_H__
#define __RELIC_H__
#include "raylib.h"
enum Type {
    WEAPON,
    WRITING,
    Artifact
};
class Relic{
    private:
        enum Type type;
        Vector2 position;
        Texture2D itemSprite;
        Texture2D weaponSprite;
        Texture2D writingSprite;


    public:
        Relic();
        ~Relic();
        void Draw();
        Vector2 GetPosition();
        void LoadSprite();
        bool CheckCollisions(Vector2 playerPos);

};
#endif // __RELIC_H__