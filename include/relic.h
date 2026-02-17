#ifndef __RELIC_H__
#define __RELIC_H__
#include "raylib.h"
enum Type {
    WEAPON,
    WRITING,
    ITEM
};
class Relic{
    private:
        enum Type type;
        Vector2 position;
        Texture2D sprite;

    public:
        Relic();
        ~Relic();

};
#endif // __RELIC_H__