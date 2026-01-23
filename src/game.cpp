#include "game.h"
#include "raytmx.h"

Game::Game(int screenWidth, int screenHeight){
    //initialize camera
    camera.target = GetPlayerPosition();
    camera.zoom = 3.0f;
    camera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
    camera.rotation = 0.0f;

    spawnPos = {40.0f, 40.0f};
    dt = GetFrameTime();

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
                    spawnPos.x = (float)(object.x + (object.width / 2.0));
                    spawnPos.y = (float)(object.y + (object.height / 2.0));
                    //TraceLog(LOG_INFO, "Spawn object position: x=%.2f, y=%.2f", object.x, object.y);
                    //TraceLog(LOG_INFO, "Spawn object size: w=%.2f, h=%.2f", object.width, object.height);
                    
                    break;
                    

                }
            }
        }
    }
    //set player position to spawn point
    player.SetPosition(spawnPos);
    camera.target = spawnPos;

    return true;

    
}

void Game::Update(){
    
    HandleInput();
    HandleCollisions();
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

        // DEBUG: Draw red circle at spawn point
        DrawCircle(40, 40, 5, RED);
        
        player.Draw();
            
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
                TraceLog(LOG_INFO, "COLLISION DETECTED! Sending player to spawn");
                player.SetPosition(spawnPos);
            }
    
            break;  // Found it, stop searching layers
        }
    }
    
}

Vector2 Game::GetPlayerPosition(){
    return player.GetPosition();
}

