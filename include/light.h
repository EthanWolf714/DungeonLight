#ifndef LIGHT_H
#define LIGHT_H
#include "raylib.h"
#include "rlgl.h"
#include <raymath.h>
#include <vector>

#define GL_SRC_ALPHA 0x0302
#define GL_MIN 0x8007
class Light
{
private:
    RenderTexture2D lightMask;
    int screenWidth;
    int screenHeight;
    int lightScale;
    Shader ditherShader;

public:
    Light(int width, int height);
    ~Light();

    void BeginLightMask(Camera2D camera, Vector2 playerPos, float playerLightRadius, std::vector<Vector2> torchPos);
    void EndLightMask();
    void RenderLightMask();
    void LoadDitherShader();
};

#endif