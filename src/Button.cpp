#include "Button.h"
#include "Scene.h"
#include "constants.h"

namespace engine
{
    Button::Button(std::string texture_name, std::string active_texture_name, Vector2 pos, float rot, float scale, int layer, bool visible, std::string text)
        : Sprite(texture_name, pos, rot, scale, layer, false, visible)
    {
        this->text = text;
        font = LoadFont("resources/fonts/Pixellari.ttf");
        animation_timer = -1;
        this->active_texture = LoadTexture(active_texture_name.c_str());
        this->inactive_texture = texture;
    }

    bool Button::IsClicked()
    {
        return MouseCollides() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && animation_timer <= 0;
    }

    void Button::Tick(Scene *scene)
    {
        if (IsClicked())
        {
            animation_timer = constants::CLICK_ANIMATION_DURATION;
        }
        if (animation_timer > 0)
        {
            ChangeTexture(active_texture);
            animation_timer--;
        }
        else
        {
            ChangeTexture(inactive_texture);
        }
    }

    void Button::Draw()
    {
        Sprite::Draw();

        DrawTextEx(font, text.c_str(), position, 30, 0, BLACK);
    }
}