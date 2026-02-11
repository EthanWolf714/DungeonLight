#include "text.h"

Text::Text(){

}

Text::~Text(){

}

void Text::DrawTextBoxSelectable(Font font, const std::string& text, Rectangle rec, float fontSize, float spacing, Color tint)
{
    int length = text.length();
    int start = 0;
    float y = rec.y;

    while (start < length){

        int end = start;
        float lineWidth = 0;
        int lastSpace = -1;

        //find how many characters fit in this line
        while(end < length && text[end] != '\n'){
            std::string singleChar(1, text[end]);
            float charWidth = MeasureText(singleChar.c_str(), fontSize);

            if(lineWidth + charWidth > rec.width){
                //wrap at last space if we found one
                if(lastSpace > start){
                    end = lastSpace + 1;
                }
                break;
            }

            if(text[end] == ' ') lastSpace = end;
            lineWidth += charWidth + spacing;
            end++;
        }

        //draw line 
        
        int lineLen = end  - start;
        if(lineLen > 0 && text[end-1] == '\n') lineLen--;
        std::string line = text.substr(start, lineLen);

        DrawText(line.c_str(), rec.x, y, fontSize, tint);


        //move to next line
        y+= fontSize * 1.5f;

        if(y + fontSize > rec.y + rec.height) break;

        start = end;
        if(start < length && text[start] == '\n') start ++;
    }
}
