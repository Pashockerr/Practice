#pragma once
#include "Sprite.h"

namespace engine
{
    class Button : public Sprite
    {
    public:
        bool IsClicked();
        Button(std::string texture_name, std::string active_texture_name, Vector2 pos, float rot, float scale, int layer, bool visible, std::string text);
        void Tick(Scene*);
        void Draw();

    private:
        int animation_timer;
        Texture active_texture;
        Texture inactive_texture;
        Font font;
        std::string text;
    };
}