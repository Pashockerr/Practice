#include "Label.h"

namespace engine
{
    Label::Label(std::string text, int font_size, Vector2 pos, float rot, float scale, int layer, bool visible)
        : Sprite("resources/textures/label.png", pos, rot, scale, layer, false, visible)
    {
        this->text = text;
        this->font_size = font_size;
    }

    void Label::Draw(){
        DrawText(text.c_str(), position.x, position.y, font_size, BLACK);
    }

    int Label::GetFontSize(){
        return font_size;
    }

    void Label::SetFontSize(int value){
        if(value > 0)
            font_size = value;
    }
}