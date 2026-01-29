#include "light.h"


Light::Light(int width, int height) :screenWidth(width), screenHeight(height) {
    //make a render texture that we can put a whole in
    // JeffM2501 example for texutre with hole in it
    lightMask = LoadRenderTexture(screenWidth, screenHeight);
}

Light::~Light(){
    UnloadRenderTexture(lightMask);
}

void Light::BeginLightMask(Camera2D camera, Vector2 playerPos, float playerLightRadius){
    //update hole where player position is
        BeginTextureMode(lightMask);
        ClearBackground(BLACK);

        //force blend mode to only set alpha of the destination
        rlSetBlendFactors(GL_SRC_ALPHA, GL_SRC_ALPHA, GL_MIN);
        rlSetBlendMode(BLEND_CUSTOM);

        //draw light mask with camera
        //this allows the light mask to be drawn in world space
        //and not screen space
        BeginMode2D(camera);
            
            //center circle to the sprites center
            float centerX = playerPos.x + (16 * 1.0) / 2.0f;
            float centerY = playerPos.y + (16 * 1.0) / 2.0f;
            //draw blank whole in texture.
            DrawCircleGradient(centerX, centerY, playerLightRadius, (Color){0,0,0,0},(Color){0,0,0,200});
           // DrawCircle(centerX, centerY, playerLightRadius, (Color){0,0,0,50});


        EndMode2D();

        //go back to normal
        rlSetBlendMode(BLEND_ALPHA);
}

void Light::EndLightMask(){
    EndTextureMode();
}

void Light::RenderLightMask(){
       // render textures are upside down from the screen, so we need to flip it to have it display correctly
        DrawTexturePro(lightMask.texture, (Rectangle){0,0, (float)screenWidth, - (float)screenHeight}, (Rectangle){0,0,(float)screenWidth, (float)screenHeight},Vector2Zero(), 0, WHITE );
}