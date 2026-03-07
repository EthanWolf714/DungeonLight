#include "door.h"
Door::Door()
{

    doorSprite = doorLockedSprite;
}

Door::~Door()
{
    
}

void Door::Draw()
{
    
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
    return true;
}

void Door::unlockDoor()
{
    unlocked = true;
}
