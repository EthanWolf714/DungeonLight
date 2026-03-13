#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include "game.h"
#include "light.h"
#include <stddef.h> /* NULL */
#include <stdlib.h> /* EXIT_FAILURE, EXIT_SUCCESS */

typedef enum GameScreen
{
    LOGO = 0,
    TITLE,
    GAMEPLAY,
    ENDING
} GameScreen;



static Sound fxLogo = {0};

static int elementPositionY = -128;
static int framesCounter = 0;
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

     TraceLog(LOG_INFO, "Logo texture loaded");
    // const float panSpeed = 150.f; // pixels per second

    // audio loading
     fxLogo = LoadSound("build/assets/audio/logo.wav");
    // TraceLog(LOG_INFO, "Logo sound loaded");
     InitAudioDevice();
    // TraceLog(LOG_INFO, "Audio device initialized");
    InitWindow(screenWidth, screenHeight, "Dungeon Light");
    TraceLog(LOG_INFO, "Window initialized");

    GameScreen currentScreen = LOGO;
    Game game(screenWidth, screenHeight);

    Light light(screenWidth, screenHeight);

    int currentFps = 60;
    SetTargetFPS(currentFps); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    TraceLog(LOG_INFO, "=== About to load map ===");
    if (!game.LoadMap("build/maps/test-map.tmx"))
    {
        TraceLog(LOG_ERROR, "MAP LOAD FAILED!");
        CloseWindow();
        return EXIT_FAILURE;
    }
    TraceLog(LOG_INFO, "=== Map loaded successfully ===");

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {

        switch (currentScreen)
        {
        case LOGO:
        {
            framesCounter++;

            elementPositionY++;
            if (elementPositionY == (screenHeight / 2 - 64 - 1)) PlaySound(fxLogo);
            if (elementPositionY > (screenHeight / 2 - 64)) elementPositionY = screenHeight / 2 - 64;
            if (framesCounter > 300)
            {
                framesCounter = 0;
                currentScreen = TITLE;
            }
        }
        break;
        case TITLE:
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                currentScreen = GAMEPLAY;
            }
        }
        break;
        case GAMEPLAY:
        {
            // Update
            //----------------------------------------------------------------------------------
            // TODO: Update your variables here
            //----------------------------------------------------------------------------------
            if (!game.IsGameOver())
            {
                game.Update();
            }
            else
            {
                currentScreen = ENDING;
            }
        }
        break;
        case ENDING:
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                currentScreen = TITLE;
            }
        }
        break;
        default:
            break;
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(DARKGREEN);
        switch (currentScreen)
        {
        case LOGO:
        {
            // Draw LOGO screen
            DrawRectangle(screenWidth/2 - 128, screenHeight/2 - 128, 256, 256, BLACK);
            DrawRectangle(screenWidth/2 - 112, screenHeight/2 - 112, 224, 224, RAYWHITE);
            DrawText("raylib", screenWidth/2 - 44, screenHeight/2 + 48, 50, BLACK);
        }
        break;
        case TITLE:
        {
            // TODO: Draw TITLE screen here!
            DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
            DrawText("Dungeon Light", 20, 20, 40, DARKGREEN);
            DrawText("PRESS ENTER to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);
        }
        break;
        case GAMEPLAY:
        {
            if (!game.IsGameOver())
            {
                game.Draw();

                auto torchPos = game.GetTorchLocations();

                light.BeginLightMask(game.GetCamera(), game.GetPlayerPosition(), game.GetPlayerLightRadius(), torchPos);
                light.EndLightMask();
                light.RenderLightMask();
                game.HandleText();
                const char *fpsText = 0;
                if (currentFps <= 0)
                    fpsText = TextFormat("FPS: unlimited (%i)", GetFPS());
                else
                    fpsText = TextFormat("FPS: %i (target: %i)", GetFPS(), currentFps);
                DrawText(fpsText, 10, 10, 20, WHITE);
            }
        }
        break;
        case ENDING:
        {
            // Draw game over screen
            DrawText("GAME OVER", 280, 130, 40, RED);
            DrawText("Press ESC to exit or Enter to Restart", 190, 200, 20, WHITE);
        }
        break;
        default:
            break;
        }
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    

     UnloadSound(fxLogo);

     CloseAudioDevice();
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}


void LogoAnimation(){
    
}