#ifndef __TEXT_H__
#define __TEXT_H__
#include "raylib.h"
#include <string>
class Text{
    private:
        Rectangle container;
        Font font;
    public:
        Text();
        ~Text();
        void Draw();
        void DrawTextBoxed(const std::string& text, Rectangle rec, float fontSize, Color tint);
        void SetBoxRect(Rectangle rect);
        Rectangle GetTextBoxRect();
        void SetPosition(float x, float y);
        void SetBoxSize(float width, float height);
        
};


#endif // __TEXT_H__