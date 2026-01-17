#include "raylib.h"
#include "game.h"
#include <stddef.h> /* NULL */
#include <stdlib.h> /* EXIT_FAILURE, EXIT_SUCCESS */

#define RAYTMX_IMPLEMENTATION
#include "raytmx.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
   // const float panSpeed = 150.f; // pixels per second

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    Game game;
    
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    TmxMap* map = LoadTMX("build/maps/test-map.tmx");
    if(map == NULL){
        TraceLog(LOG_ERROR, "Failed to load TMX map");
        CloseWindow();
        return EXIT_FAILURE;
    }

    //create camera, modified to look at the player

    Camera2D camera;
    camera.target = game.GetPlayerPosition();
    camera.zoom = 2.0f;
    camera.offset = (Vector2){screenWidth/2.0f, screenHeight/2.0f}; 
    camera.rotation = 0.0f;
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        game.Update();
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(BLACK);
            BeginMode2D(camera);
            {
                

                AnimateTMX(map);
                DrawTMX(map, NULL, NULL, 0,0,WHITE);
                game.Draw();
            }
            EndMode2D();

            //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTMX(map);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
