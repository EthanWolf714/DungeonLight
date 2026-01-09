#include "player.h"

Player::Player(){
    image = LoadTexture("build/assets/wizard.png");
    position.x = (GetScreenWidth() - image.width)/ 2;
    position.y = (GetScreenHeight() - image.height) / 2;
    frameRec = { 0.0f, 0.0f, (float)image.width/6, (float)image.height };
    frameCounter = 0;
    framesSpeed = 8;
    currentFrame = 0;
}

Player::~Player(){

}

void Player::Draw(){   

        DrawTextureRec(image, frameRec, {position.x,position.y}, WHITE);
}

void Player::Update(){
    frameCounter++;

    if (frameCounter >= (60/framesSpeed))
    {
        frameCounter = 0;
        currentFrame++;

        if (currentFrame > 5) currentFrame = 0;

        frameRec.x = (float)currentFrame*(float)image.width/6;
    }
}