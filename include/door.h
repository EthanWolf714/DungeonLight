#ifndef __DOOR_H__
#define __DOOR_H__
#include "raylib.h"


class Door{
    private:
        bool unlocked;
        Texture2D doorLockedSprite;
        Texture2D doorUnlockedSprite;
        Texture2D doorSprite;
        Vector2 position;
    public:
        Door();
        ~Door();
        void Draw();
        void setDoorSprite();
        bool isUnlocked();
        void unlockDoor();
        void SetPosition(Vector2 pos);

};

#endif // __DOOR_H__