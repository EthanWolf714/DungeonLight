#include "player.h"
#include <math.h>



Player::Player(){
    player_rightLeft = LoadTexture("build/assets/wizard_rightLeft.png");
    player_up = LoadTexture("build/assets/wizard_up.png");
    player_down = LoadTexture("build/assets/wizard_down.png");
    playerSprite = &player_down;
    position = {0,0};
    scale = 1.0f;
    frameRec = { 0.0f,0.0f,(float)playerSprite->width / 2, (float)playerSprite->height}; //start in down frame
    frameCounter = 0;
    framesSpeed = 5;
    isMoving  = false;
    direction = Direction::Down;
    facingLeft = false;
    animFrame = 0;
    
   
}

Player::~Player(){
    UnloadTexture(player_rightLeft);
    UnloadTexture(player_up);
    UnloadTexture(player_down);
}

void Player::Draw(){   
        
        Rectangle source = frameRec;
        //scale framerec
        if(facingLeft){
            source.width = -source.width;
        }
        Rectangle dest = {
            position.x, 
            position.y, 
            abs(source.width) * scale, 
            source.height * scale };
            
        Vector2 origin = {0.0f,0.0f};
        //player collision box
        DrawRectangleLines(position.x, position.y, frameRec.width *scale, frameRec.height *scale, BLUE);
        //draw player
        DrawTexturePro(*playerSprite, source, dest, origin, 0.0f, WHITE);
        
}

void Player::Update(){

   Animate();
    
}

void Player::Move(){

    
    //is player moving
   isMoving = false;
    
    // Vertical movement
    if(IsKeyDown(KEY_W)){
        isMoving = true;
        direction = Direction::Up;
        playerSprite = &player_up;
        position.y -= 1.5;
    }
    else if(IsKeyDown(KEY_S)){
        isMoving = true;
        direction = Direction::Down;
        playerSprite = &player_down;
        position.y += 1.5;
    }

    if(IsKeyDown(KEY_D)){
        isMoving = true;
        direction = Direction::Right;
        playerSprite = &player_rightLeft;
        facingLeft = false;
        position.x += 1.5;
    }
    else if(IsKeyDown(KEY_A)){
        isMoving = true;
        direction = Direction::Left;
        playerSprite = &player_rightLeft;
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

        
        frameRec.x = (float)animFrame * (float)playerSprite->width / 2;
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

