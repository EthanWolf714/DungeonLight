#ifndef __TEXT_H__
#define __TEXT_H__
#include "raylib.h"
#include <string>
class Text{
    private:
        Rectangle container;
        std::string text;
        Font font;
        bool wordWrap;
    public:
        Text();
        ~Text();
        void Draw();
        void DrawTextBoxed(Font font, std::string text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint);
        static void DrawTextBoxedSelectable(Font font, std::string text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint, int selectStart, int selectLength, Color selectTint, Color selectBackTint);

        Rectangle GetTextBoxRect();
        
};


#endif // __TEXT_H__