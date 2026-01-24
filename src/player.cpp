#include "player.h"
#include <math.h>



Player::Player(){
    player_rightLeft = LoadTexture("build/assets/wizard_rightLeft.png");
    player_up = LoadTexture("build/assets/wizard_up.png");
    player_down = LoadTexture("build/assets/wizard_down.png");
    playerSprite = &player_down; //start facing down
    position = {0,0};
    scale = 1.0f;
    frameRec = { 0.0f, 0.0f,frame_width, frame_height}; 
    isMoving  = false;
    direction = Direction::Down;
    facingLeft = false;
    speed = 90.f;
   

    
   
}

Player::~Player(){
    UnloadTexture(player_rightLeft);
    UnloadTexture(player_up);
    UnloadTexture(player_down);
}

void Player::Draw(){   
        
        Rectangle source = frameRec;
    
        if(facingLeft){
            source.width = -frame_width;
        }
        Rectangle dest = {
            position.x, 
            position.y, 
            frame_width * scale, 
            frame_height * scale };
            
        Vector2 origin = {0.0f,0.0f};
        //player collision box
        DrawRectangleLines(position.x, position.y, frame_width *scale, frame_height *scale, BLUE);
        //draw player
        DrawTexturePro(*playerSprite, source, dest, origin, 0.0f, WHITE);
        
}

void Player::Update(){

   Animate();
    
}

void Player::Move(){

    float dt = GetFrameTime();
    
    //is player moving
   isMoving = false;
    
    // Vertical movement
    if(IsKeyDown(KEY_W)){
        isMoving = true;
        direction = Direction::Up;
        playerSprite = &player_up;
        position.y -= speed * dt;
    }
    else if(IsKeyDown(KEY_S)){
        isMoving = true;
        direction = Direction::Down;
        playerSprite = &player_down;
        position.y += speed * dt;
    }
    //horizontal movement
    if(IsKeyDown(KEY_D)){
        isMoving = true;
        direction = Direction::Right;
        playerSprite = &player_rightLeft;
        facingLeft = false;
        position.x += speed * dt;
    }
    else if(IsKeyDown(KEY_A)){
        isMoving = true;
        direction = Direction::Left;
        playerSprite = &player_rightLeft;
        facingLeft = true;
        position.x -= speed * dt;
    }

}

void Player::Animate(){


    //idle frame
    if (!isMoving)
    {
        frame = 0;                
        frameRec.x = 0.0f;
        runningTime = 0.0f;
        return;
    }

    //add animation time to delta
    runningTime += GetFrameTime();

    if (runningTime >= updateTime){
        //move frame
        frame = (frame +1 ) %2;
        //update frame rectangle
        frameRec.x = frame * frame_width;
        //reset animation time
        runningTime = 0.0f;
    }
}

void Player::SetPosition(Vector2 pos){
    position = pos;
}

Vector2 Player::GetPosition(){
    return {position.x,position.y};
}

Rectangle Player::GetFrameRec(){
    
    return {
        position.x, 
        position.y, 
        abs(frameRec.width * scale),
        frameRec.height * scale
    };
}

