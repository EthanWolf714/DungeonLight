#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include "game.h"
#include "light.h"
#include <stddef.h> /* NULL */
#include <stdlib.h> /* EXIT_FAILURE, EXIT_SUCCESS */
#include <string>

// Define the 4 basic GameBoy green colors
#define GB_GREEN01 (Color){155, 188, 15, 255}
#define GB_GREEN02 (Color){110, 150, 27, 255}
#define GB_GREEN03 (Color){48, 98, 48, 255}
#define GB_GREEN04 (Color){15, 56, 15, 255}

typedef enum GameScreen
{
    LOGO = 0,
    TITLE,
    GAMEPLAY,
    ENDING
} GameScreen;

static Sound fxLogo = {0};

// Logo animation variables

static int logoPositionX;
static int logoPositionY;
static int framesCounter = 0;
static int lettersCount = 0;
static int topSideRecWidth = 16;
static int leftSideRecHeight = 16;
static int bottomSideRecWidth = 16;
static int rightSideRecHeight = 16;
static int state = 0;
static float alpha = 1.0f;

static void LogoAnimationDraw(void);
static void LogoAnimationUpdate(GameScreen& currentScreen);

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

    // Level management
    int currentLevel = 1;
    bool levelLoaded = false;

    // Logo screen variables
    
    //int elementPositionY = 0;

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {

        switch (currentScreen)
        {
        case LOGO:
        {
            LogoAnimationUpdate(currentScreen);
            
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
            // Load level if not loaded
            if (!levelLoaded)
            {
                std::string mapPath = "build/maps/level_" + std::to_string(currentLevel) + ".tmx";
                TraceLog(LOG_INFO, "=== About to load map: %s ===", mapPath.c_str());
                if (!game.LoadMap(mapPath.c_str()))
                {
                    TraceLog(LOG_ERROR, "MAP LOAD FAILED!");
                    CloseWindow();
                    return EXIT_FAILURE;
                }
                TraceLog(LOG_INFO, "=== Map loaded successfully ===");
                levelLoaded = true;
            }

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
                // Level completed, load next level
                currentLevel++;
                if (currentLevel > 3) // Assuming 2 levels
                {
                    currentScreen = ENDING;
                }
                else
                {
                    levelLoaded = false;
                }
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
            ClearBackground(GB_GREEN01);
            LogoAnimationDraw();
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

static void LogoAnimationUpdate(GameScreen& currentScreen)
{
    logoPositionX = GetScreenWidth() / 2 - 128;
    logoPositionY = GetScreenHeight() / 2 - 128;

    if (state == 0) // State 0: Small box blinking
    {
        framesCounter++;

        if (framesCounter == 120)
        {
            state = 1;
            framesCounter = 0; // Reset counter... will be used later...
        }
    }
    else if (state == 1) // State 1: Top and left bars growing
    {
        topSideRecWidth += 4;
        leftSideRecHeight += 4;

        if (topSideRecWidth == 256)
            state = 2;
    }
    else if (state == 2) // State 2: Bottom and right bars growing
    {
        bottomSideRecWidth += 4;
        rightSideRecHeight += 4;

        if (bottomSideRecWidth == 256)
            state = 3;
    }
    else if (state == 3) // State 3: Letters appearing (one by one)
    {
        framesCounter++;

        if (framesCounter / 12) // Every 12 frames, one more letter!
        {
            lettersCount++;
            framesCounter = 0;
        }

        if (lettersCount >= 10) // When all letters have appeared, just fade out everything
        {
            alpha -= 0.02f;

            if (alpha <= 0.0f)
            {
                alpha = 0.0f;
                state = 4;
                currentScreen = TITLE;
            }
        }
    }
}


static void LogoAnimationDraw(void)
{

    if (state == 0)
    {
        if ((framesCounter / 15) % 2)
            DrawRectangle(logoPositionX, logoPositionY, 16, 16, GB_GREEN03);
    }
    else if (state == 1)
    {
        DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, GB_GREEN03);
        DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, GB_GREEN03);
    }
    else if (state == 2)
    {
        DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, GB_GREEN03);
        DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, GB_GREEN03);

        DrawRectangle(logoPositionX + 240, logoPositionY, 16, rightSideRecHeight, GB_GREEN03);
        DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, GB_GREEN03);
    }
    else if (state == 3)
    {
        DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, Fade(GB_GREEN03, alpha));
        DrawRectangle(logoPositionX, logoPositionY + 16, 16, leftSideRecHeight - 32, Fade(GB_GREEN03, alpha));

        DrawRectangle(logoPositionX + 240, logoPositionY + 16, 16, rightSideRecHeight - 32, Fade(GB_GREEN03, alpha));
        DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, Fade(GB_GREEN03, alpha));

        DrawRectangle(GetScreenWidth() / 2 - 112, GetScreenHeight() / 2 - 112, 224, 224, Fade(GB_GREEN01, alpha));

        DrawText(TextSubtext("raylib", 0, lettersCount), GetScreenWidth() / 2 - 44, GetScreenHeight() / 2 + 48, 50, Fade(GB_GREEN03, alpha));
    }
}