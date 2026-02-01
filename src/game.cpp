#include "game.h"
#include "raytmx.h"


Game::Game(int screenWidth, int screenHeight) : camera(screenWidth, screenHeight)
{
    //camera.setCameraTarget(GetPlayerPosition());

    dt = 0.0f;
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
        torches.emplace_back(pos, 0.3);
    }

    // set player position to spawn point
    player.SetPosition(currentMap.GetSpawnPosition());
    camera.setCameraTarget(currentMap.GetSpawnPosition());
    
   

    return true;
}

std::vector<Vector2> Game::GetTorchLocations()
{
    return currentMap.GetTorchPositions();
}

void Game::Update()
{
    dt = GetFrameTime();
    HandleInput();
    HandleCollisions();
    player.Update(dt);

    for(Torch& t : torches){
        t.CheckCollisions(player);
    }

    // update camera position to target player
    camera.setCameraTarget(GetPlayerPosition());
}

void Game::Draw()
{

    BeginMode2D(camera.GetCamera());
    {
        // TraceLog(LOG_INFO, "Drawing map");
        currentMap.Draw(0, 0, WHITE);
        
        for(Torch& t : torches){
            if(!t.IsConsumed()){
                t.Draw();
            }
        }
        

        // DEBUG: Draw red circle at spawn point
        // DrawCircle(40, 40, 5, RED);

        player.Draw();

        // DrawCollisionDebug();
    }
    EndMode2D();
}

void Game::HandleInput()
{
    player.Move();
}

void Game::HandleCollisions()
{
    // get wall collisions objects
    const std::vector<Rectangle> &walls = currentMap.GetCollisionBoxes();
    Rectangle playerRec = player.GetFrameRec();
    // loop through wall collisions
    for (const Rectangle &wall : walls)
    {
        bool collided = CheckCollisionRecs(playerRec, wall);

        if (collided)
        {
            player.UndoMovement();
            break;
        }
    }
}

Vector2 Game::GetPlayerPosition()
{
    return player.GetPosition();
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
    // draw each wall box
    for (const Rectangle &wall : walls)
    {

        DrawRectangleLinesEx(wall, 2.0f, RED);
        DrawRectangle(wall.x, wall.y, wall.width, wall.height, Fade(RED, 0.2f));
    }

    // Draw player collision rectangle
    Rectangle playerRec = player.GetFrameRec();
    DrawRectangleLinesEx(playerRec, 2.0f, GREEN);
    DrawRectangle(playerRec.x, playerRec.y, playerRec.width, playerRec.height, Fade(GREEN, 0.2f));
}

float Game::GetPlayerLightRadius()
{
    return player.GetLightRadius();
}
