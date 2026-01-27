#ifndef CAMERA_H
#define CAMERA_H

#include "raylib.h"
#include "player.h"

class GameCamera
{
private:
    Camera2D camera;
    

public:
    GameCamera(int screenWidth, int screenHeight);
    ~GameCamera();
    void setCameraTarget(Vector2 targetPos);
    Camera2D GetCamera();
};



#endif
