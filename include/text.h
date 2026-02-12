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
        Rectangle GetTextBoxRect();
        static void DrawTextBoxSelectable(const std::string& text, Rectangle rec, float fontSize,Color tint);

};


#endif // __TEXT_H__