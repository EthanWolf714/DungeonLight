#include "player.h"

Player::Player(){
    image = LoadTexture("build/assets/wizard.png");
    position.x = (GetScreenWidth() - image.width)/ 2;
    position.y = (GetScreenHeight() - image.height) / 2;
    scale = 1.0f;
    frameRec = { 0.0f, 0.0f, (float)image.width/6, (float)image.height };
    frameCounter = 0;
    framesSpeed = 4;
    currentFrame = 0;
    isMoving  = false;
    lastDirectionMoved = 1;
}

Player::~Player(){

}

void Player::Draw(){   

        Rectangle source = frameRec;
        //scale framerec
        Rectangle dest = {position.x, position.y, frameRec.width * scale, frameRec.height * scale};

        Vector2 origin = {0.0f, 0.0f};
        //draw player
        DrawTexturePro(image, source, dest, origin, 0.0f, WHITE);
}

void Player::Update(){

    //if moving up or down call UpDown animation
   if(isMovingUp || isMovingDown){
        AnimateUpDown();
   }else{
        AnimateLeftRight();
   }

    isMovingUp = false;
    isMovingDown = false;
    
}

void Player::Move(){
    
    if(IsKeyDown(KEY_W)){
        isMoving = true;
        isMovingUp = true;
        lastDirectionMoved = 0;
        position.y -= 1.5;
        
    }else if(IsKeyDown(KEY_S)){
        isMoving = true;
         isMovingDown = true;
         lastDirectionMoved = 1;
        position.y += 1.5;
       
    }else if(IsKeyDown(KEY_D)){
        isMoving = true;
        position.x += 1.5;
        //flip sprite base on direction moved
        if(frameRec.width < 0){
             frameRec.width = -frameRec.width;
        }
        
    }else if(IsKeyDown(KEY_A)){
        isMoving = true;
        position.x -= 1.5;
        if(frameRec.width > 0){
             frameRec.width = -frameRec.width;
        }
       
    }else{
        isMoving = false;
    }
}

void Player::AnimateLeftRight(){
     frameCounter++;
    if (frameCounter >= (60/framesSpeed))
    {
        frameCounter = 0;
        if(isMoving){
            currentFrame++;

            if (currentFrame > 1) //cycle between 0 and 1
            {
                currentFrame = 0;
            }
            
        }
        frameRec.x = (float)currentFrame*(float)image.width/6;

        
    }
}

void Player::AnimateUpDown(){
    frameCounter++;
    if (frameCounter >= (60/framesSpeed))
    {
        frameCounter = 0;
        if(isMoving){
            if(isMovingUp){
                currentFrame++;
                if (currentFrame < 2 || currentFrame > 3) //cycle between 2 and 3
                {
                    currentFrame = 2;
                }

            
            }
            else if(isMovingDown){
                currentFrame++;
                if( currentFrame < 4 || currentFrame > 5)//cycle between 4 and 5
                {
                    currentFrame = 4;
                }
                
            }
            
            
        }else{
           currentFrame = (lastDirectionMoved == 0) ? 2 : 4;
        }
        frameRec.x = (float)currentFrame*(float)image.width/6;

        
    }
}

Vector2 Player::GetPosition(){
    return position;
}
