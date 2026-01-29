#include "game.h"
#include "raytmx.h"

Game::Game(int screenWidth, int screenHeight) : camera(screenWidth, screenHeight){

    camera.setCameraTarget(GetPlayerPosition());

    spawnPos = {40.0f, 40.0f};
    dt = 0.0f;

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
    
    

    //loop through tilemap layers
    for(unsigned int i = 0; i < map->layersLength; i++){
        const TmxLayer layer = map->layers[i];
        //loop through objects group
        if(layer.type == LAYER_TYPE_OBJECT_GROUP){
            TmxObjectGroup objGroup = layer.exact.objectGroup;
            //loop through object layer
            for(unsigned int j = 0; j < objGroup.objectsLength; j++){
                const TmxObject object = objGroup.objects[j];
                //location spawn point object
                if(object.name != NULL && strcmp(object.name, "spawn") == 0){
                    //offset spawn positition for player sprite
                    spawnPos.x = object.x - 8;
                    spawnPos.y = object.y - 8;
                    //TraceLog(LOG_INFO, "Spawn object position: x=%.2f, y=%.2f", object.x, object.y);
                    //TraceLog(LOG_INFO, "Spawn object size: w=%.2f, h=%.2f", object.width, object.height);
                    
                    break;
                    

                }
            }
        }
    }
    //set player position to spawn point
    player.SetPosition(spawnPos);
    camera.setCameraTarget(spawnPos);

    return true;

    
}

void Game::Update(){
    dt = GetFrameTime();
    HandleInput();
    HandleCollisions();
    player.Update(dt);
    
    //update camera position to target player
    camera.setCameraTarget(GetPlayerPosition());

    
}

void Game::Draw(){
    
    BeginMode2D(camera.GetCamera());
    {
        //draw map first(background)
        if(map != nullptr){
            AnimateTMX(map);
            DrawTMX(map, NULL, NULL, 0, 0, WHITE);
        }

        // DEBUG: Draw red circle at spawn point
        //DrawCircle(40, 40, 5, RED);
        
        player.Draw();
            
        //DrawCollisionDebug();
    }
    EndMode2D();
}

void Game::HandleInput(){
    player.Move();
}


void Game::HandleCollisions(){
    TmxObjectGroup wallsObjectGroup = {};

    for(unsigned int i = 0; i < map->layersLength; i++){
        const TmxLayer layer = map->layers[i];
        if(strcmp(layer.name, "Walls") == 0 && layer.type == LAYER_TYPE_OBJECT_GROUP){
            wallsObjectGroup = layer.exact.objectGroup;
            
            Rectangle playerRec = player.GetFrameRec();
            
            bool collided = CheckCollisionTMXObjectGroupRec(wallsObjectGroup, playerRec, NULL);
            
         

            if(collided){
                //TraceLog(LOG_INFO, "COLLISION DETECTED! Sending player to spawn");
                player.UndoMovement();
            }
    
            break;  // Found it, stop searching layers
        }
    }
    
}

Vector2 Game::GetPlayerPosition(){
    return player.GetPosition();
}

Camera2D Game::GetCamera(){
    return camera.GetCamera();
}

//tool to visualize collisions (made with AI)
void Game::DrawCollisionDebug(){
    if(map == nullptr) return;
    
    for(unsigned int i = 0; i < map->layersLength; i++){
        const TmxLayer layer = map->layers[i];
        if(strcmp(layer.name, "Walls") == 0 && layer.type == LAYER_TYPE_OBJECT_GROUP){
            TmxObjectGroup wallsObjectGroup = layer.exact.objectGroup;
            
            // Draw collision objects (in world space, camera transform is already applied)
            for(unsigned int j = 0; j < wallsObjectGroup.objectsLength; j++){
                const TmxObject obj = wallsObjectGroup.objects[j];
                
                Rectangle rec = {
                    (float)obj.x,
                    (float)obj.y,
                    (float)obj.width,
                    (float)obj.height
                };
                
                DrawRectangleLinesEx(rec, 2.0f, RED);
                DrawRectangle(rec.x, rec.y, rec.width, rec.height, Fade(RED, 0.2f));
            }
            
            // Draw player collision rectangle
            Rectangle playerRec = player.GetFrameRec();
            DrawRectangleLinesEx(playerRec, 2.0f, GREEN);
            DrawRectangle(playerRec.x, playerRec.y, playerRec.width, playerRec.height, Fade(GREEN, 0.2f));
            
            break;
        }
    }
}

float Game::GetPlayerLightRadius(){
    return player.GetLightRadius();
}
