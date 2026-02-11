#ifndef __TEXT_H__
#define __TEXT_H__
#include "raylib.h"
#include <string>
class Text{
    private:
        Rectangle textBox;
        std::string text;
    public:
        Text();
        ~Text();
        void DrawTextBox();
        static void DrawTextBoxSelectable(Font font, const std::string& text, Rectangle rec, float fontSize, float spacing, Color tint);

};


#endif // __TEXT_H__