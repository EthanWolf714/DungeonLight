#include "camera.h"

GameCamera::GameCamera(int screenWidth, int screenHeight)
{
    //initialize camera
    camera.zoom = 3.0f;
    camera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
    camera.rotation = 0.0f;
}

GameCamera::~GameCamera()
{
}

Camera2D GameCamera::GetCamera(){
    return camera;
}

void GameCamera::setCameraTarget(Vector2 targetPos){
    camera.target = targetPos;
}