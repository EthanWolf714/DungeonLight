#include "game.h"
#include "raytmx.h"

Game::Game(int screenWidth, int screenHeight){
    //initialize camera
    camera.target = GetPlayerPosition();
    camera.zoom = 3.0f;
    camera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
    camera.rotation = 0.0f;

    map = nullptr;
}

Game::~Game(){
    if(map != nullptr){
        UnloadTMX(map);
    }
}

bool Game::LoadMap(const char* filepath){
    //initialize tile map
    map = LoadTMX(filepath);
    if (map == NULL)
    {
        TraceLog(LOG_ERROR, "Failed to load TMX map");
        return false;

    }
    TraceLog(LOG_INFO, "Map Loaded Successfully!");
    return true;
}

void Game::Update(){
    
    HandleInput();
    player.Update();
    
    //update camera position to target player
    camera.target = GetPlayerPosition();
}

void Game::Draw(){
    
    BeginMode2D(camera);
    {
        //draw map first(background)
        if(map != nullptr){
            AnimateTMX(map);
            DrawTMX(map, NULL, NULL, 0, 0, WHITE);
        }
        
        player.Draw();
            
    }
    EndMode2D();
}

void Game::HandleInput(){
    player.Move();
}

Vector2 Game::GetPlayerPosition(){
    return player.GetPosition();
}

