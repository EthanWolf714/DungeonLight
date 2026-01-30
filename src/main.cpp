#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include "game.h"
#include "light.h"
#include <stddef.h> /* NULL */
#include <stdlib.h> /* EXIT_FAILURE, EXIT_SUCCESS */


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

    InitWindow(screenWidth, screenHeight, "Dungeon Light");

    Game game(screenWidth, screenHeight);

     Light light(screenWidth, screenHeight);

    int currentFps = 60;
    SetTargetFPS(currentFps); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    

    if(!game.LoadMap("build/maps/test-map.tmx")){
        CloseWindow();
        return EXIT_FAILURE;
    }
    
   

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
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
            
            game.Draw();
           
            light.BeginLightMask(game.GetCamera(), game.GetPlayerPosition(), game.GetPlayerLightRadius());
            light.EndLightMask();
            light.RenderLightMask();
            
            const char *fpsText = 0;
            if (currentFps <= 0) fpsText = TextFormat("FPS: unlimited (%i)", GetFPS());
            else fpsText = TextFormat("FPS: %i (target: %i)", GetFPS(), currentFps);
            DrawText(fpsText, 10, 10, 20, WHITE);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
