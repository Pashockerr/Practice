#include "Label.h"

namespace engine
{
    Label::Label(std::string text, int font_size, Vector2 pos, float rot, float scale, int layer, bool visible)
        : Sprite("resources/textures/label.png", pos, rot, scale, layer, false, visible)
    {
        int codepoints[512] = {0};
        for (int i = 0; i < 95; i++)
            codepoints[i] = 32 + i; // Basic ASCII characters
        for (int i = 0; i < 255; i++)
            codepoints[96 + i] = 0x400 + i; // Cyrillic characters
        this->text = text;
        this->font_size = font_size;
        font = LoadFontEx("resources/fonts/Pixellari.ttf", font_size, codepoints, 512);
    }

    void Label::Draw()
    {
        DrawTextEx(font, text.c_str(), position, font_size, 1, BLACK);
    }

    int Label::GetFontSize()
    {
        return font_size;
    }

    void Label::SetFontSize(int value)
    {
        if (value > 0)
            font_size = value;
    }
}