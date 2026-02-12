#include "text.h"

Text::Text(){
    
}

Text::~Text(){

}

Rectangle Text::GetTextBoxRect()
{
    return textBox;
}

void Text::DrawTextBoxSelectable( const std::string& text, Rectangle rec, float fontSize,Color tint)
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
