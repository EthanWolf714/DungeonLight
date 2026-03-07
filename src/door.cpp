#include "door.h"
Door::Door()
{
    doorLockedSprite = LoadTexture("build/assets/Door_Locked.png");
    doorUnlockedSprite = LoadTexture("build/assets/Door_Unlocked.png");
    unlocked = false;
    doorSprite = doorLockedSprite;
}

Door::~Door()
{
    UnloadTexture(doorLockedSprite);
    UnloadTexture(doorUnlockedSprite);
}

void Door::Draw()
{
    DrawTexture(doorSprite, position.x, position.y, WHITE);
}

void Door::setDoorSprite()
{
    if(unlocked){
        doorSprite = doorUnlockedSprite;

    }else{
        doorSprite = doorLockedSprite;
    }
}

bool Door::isUnlocked()
{
    return unlocked;
}

void Door::unlockDoor()
{
    unlocked = true;
}

void Door::SetPosition(Vector2 pos)
{
    pos = position;
}
