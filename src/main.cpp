#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include "game.h"
#include <stddef.h> /* NULL */
#include <stdlib.h> /* EXIT_FAILURE, EXIT_SUCCESS */

#define GL_SRC_ALPHA 0x0302
#define GL_MIN 0x8007
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

    //make a render texture that we can put a whole in
    // JeffM2501 example for texutre with hole in it
    RenderTexture2D lightMask = LoadRenderTexture(screenWidth, screenHeight);

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    if(!game.LoadMap("build/maps/test-map.tmx")){
        CloseWindow();
        return EXIT_FAILURE;
    }
    
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        //update hole where player position is
        BeginTextureMode(lightMask);
        ClearBackground(BLACK);

        
        //force blend mode to only set alpha of the destination
        rlSetBlendFactors(GL_SRC_ALPHA, GL_SRC_ALPHA, GL_MIN);
        rlSetBlendMode(BLEND_CUSTOM);

        //draw light mask with camera
        BeginMode2D(game.GetCamera());

            Vector2 playerPos = game.GetPlayerPosition();
            //center circle to the sprites center
            float centerX = playerPos.x + (16 * 1.0) / 2.0f;
            float centerY = playerPos.y + (16 * 1.0) / 2.0f;
            //draw blank whole in texture.
            DrawCircle(centerX, centerY, 30, BLANK );

        EndMode2D();
        //go back to normal
        rlSetBlendMode(BLEND_ALPHA);

        EndTextureMode();
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
              // render textures are upside down from the screen, so we need to flip it to have it display correctly
            DrawTexturePro(lightMask.texture, (Rectangle){0,0, screenWidth, - screenHeight}, (Rectangle){0,0,screenWidth, screenHeight},Vector2Zero(), 0, WHITE );
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadRenderTexture(lightMask);
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
