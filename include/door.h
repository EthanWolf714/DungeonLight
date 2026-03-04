#ifndef __DOOR_H__
#define __DOOR_H__
#include "raylib.h"


class Door{
    private:
        bool unlocked;
        Texture2D doorSprite;
    public:
        Door();
        ~Door();
        void Draw();
        void setDoorSprite();
        bool isUnlocked();
        void unlockDoor();

};

#endif // __DOOR_H__