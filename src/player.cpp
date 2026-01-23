#include "player.h"
#include <math.h>



Player::Player(){
    image = LoadTexture("build/assets/wizard.png");
    position = {0,0};
    scale = 1.0f;
    frameRec = { 4.0f * (float)image.width/6, 0.0f, (float)image.width/6, (float)image.height}; //start in down frame
    frameCounter = 0;
    framesSpeed = 5;
    isMoving  = false;
    direction = Direction::Down;
    facingLeft = false;
    animFrame = 0;
   
}

Player::~Player(){
    UnloadTexture(image);
}

void Player::Draw(){   
        
        Rectangle source = frameRec;
        //scale framerec
        if(facingLeft){
            source.width = -source.width;
        }
        Rectangle dest = {position.x, 
            position.y, 
            abs(source.width) * scale, 
            frameRec.height * scale };
            
        Vector2 origin = {0.0f,0.0f};
        DrawRectangleLines(position.x, position.y, frameRec.width *scale, frameRec.height *scale, BLUE);
        //draw player
        DrawTexturePro(image, source, dest, origin, 0.0f, WHITE);
        
}

void Player::Update(){

   Animate();
    
}

void Player::Move(){

    
    
   isMoving = false;
    
    // Vertical movement
    if(IsKeyDown(KEY_W)){
        isMoving = true;
        direction = Direction::Up;
        position.y -= 1.5;
    }
    else if(IsKeyDown(KEY_S)){
        isMoving = true;
        direction = Direction::Down;
        position.y += 1.5;
    }
    
    // Horizontal movement (can override vertical for animation)
    if(IsKeyDown(KEY_D)){
        isMoving = true;
        direction = Direction::Right;
        facingLeft = false;
        position.x += 1.5;
    }
    else if(IsKeyDown(KEY_A)){
        isMoving = true;
        direction = Direction::Left;
        facingLeft = true;
        position.x -= 1.5;
    }

}

void Player::Animate(){
    frameCounter++;
    if (frameCounter >= (60 / framesSpeed)){
        frameCounter = 0;
        
        if(isMoving){
            animFrame = (animFrame == 0) ? 1 : 0;  // Toggle between 0 and 1
        } else {
            animFrame = 0;  // Idle on first frame
        }
        
        // Calculate frame based on direction and animation frame
        int frameIndex = 0;
        
        switch(direction){
            case Direction::Right:
            case Direction::Left:
                frameIndex = animFrame;  // Frames 0-1 for horizontal
                break;
            case Direction::Up:
                frameIndex = 2 + animFrame;  // Frames 2-3 for up
                break;
            case Direction::Down:
                frameIndex = 4 + animFrame;  // Frames 4-5 for down
                break;
        }
        
        frameRec.x = (float)frameIndex * (float)image.width / 6;
    }
}

void Player::SetPosition(Vector2 pos){
    position = pos;
}

Vector2 Player::GetPosition(){
    return position;
}

Rectangle Player::GetFrameRec(){
    
    return {
        position.x, 
        position.y, 
        abs(frameRec.width * scale),
        frameRec.height * scale
    };
}

