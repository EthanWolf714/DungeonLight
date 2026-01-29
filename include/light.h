#ifndef LIGHT_H
#define LIGHT_H
#include "raylib.h"
#include "rlgl.h"
#include <raymath.h>


#define GL_SRC_ALPHA 0x0302
#define GL_MIN 0x8007
class Light{
    private:
        RenderTexture2D lightMask;
        int screenWidth;
        int screenHeight;
    public:
        Light(int width, int height);
        ~Light();

        void BeginLightMask(Camera2D camera, Vector2 playerPos);
        void EndLightMask();
        void RenderLightMask();

};


#endif