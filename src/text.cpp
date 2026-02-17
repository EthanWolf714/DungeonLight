#include "text.h"


Text::Text(){
    container =  { 25.0f, GetScreenHeight() - 60.0f, GetScreenWidth() - 50.0f, GetScreenHeight() - 400.0f };
    font = GetFontDefault();
    
}

Text::~Text(){

}


void Text::DrawTextBoxed(const std::string& text, Rectangle rec, float fontSize, Color tint){
    //TraceLog(LOG_INFO, "DrawTextBoxed called! text='%s' rec.x=%f rec.y=%f", 
        // text.c_str(), rec.x, rec.y);
    //TraceLog(LOG_INFO, "DrawTextBoxedSelectable START: length=%d", text.length());
    
     int length = text.length();
    int start = 0;
    float y = rec.y;
    //TraceLog(LOG_INFO, "Before loop: length=%d start=%d", length, start);
    while (start < length){
        //TraceLog(LOG_INFO, "INSIDE LOOP");
        int end = start;
        int lastSpace = -1;

        //find how many characters fit in this line
        while(end < length && text[end] != '\n'){
             //TraceLog(LOG_INFO, "Inner loop: end=%d char='%c'", end, text[end]);
            std::string currentLine  = text.substr(start, end - start + 1);
            float lineWidth = MeasureText(currentLine.c_str(), fontSize);


            //TraceLog(LOG_INFO, "lineWidth=%f rec.width=%f", lineWidth, rec.width);
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
        //TraceLog(LOG_INFO, "About to draw: '%s'", line.c_str());
        DrawText(line.c_str(), rec.x, y, fontSize, tint);


        //move to next line
        y+= fontSize * 1.5f;
        if(y + fontSize > rec.y + rec.height) break;

        start = end;
    }
}

void Text::SetBoxRect(Rectangle rect)
{
    container = rect;
}


Rectangle Text::GetTextBoxRect()
{
    return container;
}

void Text::SetPosition(float x, float y) {
    container.x = x;
    container.y = y;
}

void Text::SetBoxSize(float width, float height)
{
    container.width = width;
    container.height = height;
}

