#include "game.h"
#include "raytmx.h"


Game::Game(int screenWidth, int screenHeight) : camera(screenWidth, screenHeight)
{
    //camera.setCameraTarget(GetPlayerPosition());
    dt = 0.0f;
    dialogOpen = false;
    dialogText = "";
    coolDown = 0.0f;
    
    
    isGameOver = false;
    
}

Game::~Game()
{
    
}

bool Game::LoadMap(const char *filepath)
{ 
    // initialize tile map
    if (!currentMap.Load(filepath))
    {
        return false;
    }

    for(Vector2 pos: currentMap.GetTorchPositions()){
        entityManager.SpawnTorch(pos, 0.3);
    }

    entityManager.ReserveRelics(currentMap.GetInteractableObjects().size());

    // spawn relics from interactable objects
    for (const Map::Interactable &object : currentMap.GetInteractableObjects())
    {
        if (object.name == "Item")
            entityManager.SpawnRelic({object.rect.x, object.rect.y}, Type::ITEM);
        else if (object.name == "Weapon")
            entityManager.SpawnRelic({object.rect.x, object.rect.y}, Type::WEAPON);
        else if (object.name == "Writing")
            entityManager.SpawnRelic({object.rect.x, object.rect.y}, Type::WRITING);
    }

    // set player position to spawn point
    entityManager.SetPlayerPos(currentMap.GetSpawnPosition());
    camera.setCameraTarget(currentMap.GetSpawnPosition());
    relics = currentMap.GetRelicCount();
    relicCount = 0;
    TraceLog(LOG_INFO, "relics: %d, relicCount: %d", relics, relicCount);
    return true;
}

std::vector<Vector2> Game::GetTorchLocations()
{
    std::vector<Vector2> positions;
    for(Torch& torch : entityManager.GetTorches()){
        if(!torch.IsConsumed()){
            positions.push_back(torch.GetPosition());
        }
    }
    return positions;
}

void Game::HandleText()
{
    if(dialogOpen){
        
        //TraceLog(LOG_INFO, "Dialog opened!");
        Rectangle rect = interactMessage.GetTextBoxRect();
        //TraceLog(LOG_INFO, "Drawing dialog! Rect: x=%f y=%f w=%f h=%f", 
                //rect.x, rect.y, rect.width, rect.height);
        DrawRectangleRec(rect, BLACK); // Draw background
        DrawRectangleLinesEx(rect, 2, WHITE); // Draw border
        interactMessage.DrawTextBoxed(dialogText, interactMessage.GetTextBoxRect(), 20.0f, WHITE);
            

    }

     

    if(coolDown > 0.0f){
        coolDown -= dt;
        TraceLog(LOG_INFO, "Countdown started: %.1f", coolDown);
        
    }else{
        dialogOpen = false;
    }
}

bool Game::IsGameOver()
{
    if(!entityManager.GetPlayerActivity()){
         TraceLog(LOG_INFO, "Game over: player inactive");
        return true;
    }

    int totalRelics = entityManager.GetRelics().size();
    if(relicCount == totalRelics && relics > 0){
        TraceLog(LOG_INFO, "Game over: relics collected");
        return true;
    }
            
    return false;
}


void Game::Update()
{
    dt = GetFrameTime();
    HandleInput();
    HandleCollisions();
    entityManager.Update(dt);
    int newCount = 0;
    for (Relic &relic : entityManager.GetRelics())
    {   
        if (relic.IsCollected()){
            newCount ++;
            
            
        }
        //only trigger when count increases
        if(newCount > relicCount){
            dialogOpen = true;
            dialogText = "Relic Found";
            coolDown = 3.0f;
        }
    }

    relicCount = newCount;
    //TraceLog(LOG_INFO, "Torch count: %d", torches.size());
    // update camera position to target player
    camera.setCameraTarget(entityManager.GetPlayerPos());
}



void Game::Draw()
{

    BeginMode2D(camera.GetCamera());
    {
        
        // TraceLog(LOG_INFO, "Drawing map");
        currentMap.Draw(0, 0, WHITE);
        
        entityManager.Draw();
        // DEBUG: Draw red circle at spawn point
        // DrawCircle(40, 40, 5, RED);
        const std::vector<Map::Interactable> &objects = currentMap.GetInteractableObjects();
       
        for(const Map::Interactable &object : objects){ 
            DrawRectangleLinesEx(object.rect, 2, GREEN);     
        }
         //DrawCollisionDebug();
        
    }
    EndMode2D();
    
}

void Game::HandleInput()
{
    entityManager.GetPlayerInput();
}

void Game::HandleCollisions()
{
    // get wall collisions objects
    const std::vector<Rectangle> &walls = currentMap.GetCollisionBoxes();
    Rectangle playerRec = entityManager.GetPlayerCollisionRec();
    // loop through wall collisions
    for (const Rectangle &wall : walls)
    {
        bool collided = CheckCollisionRecs(playerRec, wall);

        if (collided)
        {
            entityManager.UndoPlayerMovement();
            entityManager.UpdatePlayerRects();
            break;
        }
    }

    const std::vector<Map::Interactable> &objects = currentMap.GetInteractableObjects();
    //TraceLog(LOG_INFO, "Number of objects: %d", objects.size());
    Rectangle playerInteractCollision = entityManager.GetPlayerInteractRec();
    
   //bool dialogOpen = false;

    for(const Map::Interactable &object : objects){ 
           
        bool collided = CheckCollisionRecs(playerInteractCollision, object.rect);
        
        if(collided){
            
           //TraceLog(LOG_INFO, "Interactable object collided");
            if(IsKeyPressed(KEY_E) && coolDown <= 0.0f){
                dialogOpen = true;
                dialogText = "LALALALALALALALALA";
                coolDown = 3.0f;
              // TraceLog(LOG_INFO, "dialog open");
                
            }

            
            
           
        }
        
    }
}

Vector2 Game::GetPlayerPosition()
{
    return entityManager.GetPlayerPos();
}

Camera2D Game::GetCamera()
{
    return camera.GetCamera();
}

// tool to visualize collisions
void Game::DrawCollisionDebug()
{

    // get wall collisions objects
    const std::vector<Rectangle> &walls = currentMap.GetCollisionBoxes();
    //const std::vector<Rectangle> &objects = currentMap.GetInteractableObjects();
   
    for (const Rectangle &wall : walls)
    {

        DrawRectangleLinesEx(wall, 2.0f, RED);
        DrawRectangle(wall.x, wall.y, wall.width, wall.height, Fade(RED, 0.2f));
    }

    


    // Draw player collision rectangle
    //Rectangle playerRec = entityManager.GetPlayerFrameRec();
    //DrawRectangleLinesEx(playerRec, 2.0f, GREEN);
    //DrawRectangle(playerRec.x, playerRec.y, playerRec.width, playerRec.height, Fade(GREEN, 0.2f));
}

float Game::GetPlayerLightRadius()
{
    return entityManager.GetPlayerLightRadius();
}


