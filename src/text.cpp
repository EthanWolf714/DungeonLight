#include "text.h"

Text::Text(){
    container =  { 25.0f, 25.0f, GetScreenWidth() - 50.0f, GetScreenHeight() - 250.0f };
    font = GetFontDefault();
    wordWrap = false;
}

Text::~Text(){

}

void Text::Draw()
{
    DrawRectangleLinesEx(container, 3, GREEN);
    DrawTextBoxed(font, text, (Rectangle){ container.x + 4, container.y + 4, container.width - 4, container.height - 4 }, 20.0f, 2.0f, wordWrap, GRAY);

}

void Text::DrawTextBoxed(Font font, std::string text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint){
    DrawTextBoxedSelectable(font, text, rec, fontSize, spacing, wordWrap, tint, 0,0,WHITE,WHITE);
}

void Text::DrawTextBoxedSelectable(Font font, std::string text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint, int selectStart, int selectLength, Color selectTint, Color selectBackTint)
{
     int length = text.length();
    int start = 0;
    float y = rec.y;

    while (start < length){

        int end = start;
        int lastSpace = -1;

        //find how many characters fit in this line
        while(end < length && text[end] != '\n'){
            std::string singleChar(1, text[end]);
            float lineWidth = MeasureText(singleChar.c_str(), fontSize);

            if(lineWidth > rec.width){
                //wrap at last space if we found one
                if(lastSpace > start){
                    end = lastSpace;
                }
                break;
            }

            if(text[end] == ' ') lastSpace = end;
            end++;
        }

        //draw line 
        std::string line = text.substr(start, end - start);

        DrawText(line.c_str(), rec.x, y, fontSize, tint);


        //move to next line
        y+= fontSize * 1.5f;
        if(y + fontSize > rec.y + rec.height) break;

        start = end;
    }
}

Rectangle Text::GetTextBoxRect()
{
    return container;
}


