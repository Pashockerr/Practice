#include "Terminal.h"
#include <math.h>
#include <iostream>
#include "Scene.h"

namespace engine
{
    const Vector2 RECIEVER_REL_POS{870, 610};
    const Vector2 TEXT_REL_POS{500, 500};
    const Vector2 KEYBOARD_REL_POS{870, 170};
    const Vector2 HELPER_REL_POS{780, 0};
    const float KEYBOARD_MARGIN = 10;
    const float BUTTON_SIDE = 100;

    Terminal::Terminal(std::string texture_name, Vector2 pos, float rot, float scale, int layer, bool visible, Scene *scene)
        : Sprite(texture_name, pos, rot, scale, layer, false, visible)
    {

        reciever = new Reciever("resources/textures/port.png", {pos.x + RECIEVER_REL_POS.x, pos.y + RECIEVER_REL_POS.y},
                                0, 1, 2, true);
        scene->sprites.push_front(reciever);

        helper = new Sprite("resources/textures/helper.png", {pos.x + HELPER_REL_POS.x, pos.y + HELPER_REL_POS.y},
                            0, 1, 1, false, true);
        scene->sprites.push_front(helper);

        for (int i = 0; i < 12; i++)
        {
            auto button = new engine::Button("resources/textures/button_inactive.png",
                                             "resources/textures/button_active.png",
                                             {pos.x + KEYBOARD_REL_POS.x + (i % 3) * BUTTON_SIDE + (i % 3) * KEYBOARD_MARGIN,
                                              pos.y + KEYBOARD_REL_POS.y + (float)std::floor(i / 3) * BUTTON_SIDE + (float)std::floor(i / 3) * KEYBOARD_MARGIN},
                                             0, 1, 2, true);
            keyboard.push_front(button);
            scene->sprites.push_front(button);
        }
    }

    void Terminal::Tick(Scene *scene)
    {
    }

    void Terminal::Draw()
    {
        Sprite::Draw();

        DrawText(reciever->values.empty() ? "Didn't recieve" : std::to_string(reciever->values.front()).c_str(), position.x + TEXT_REL_POS.x, position.y + TEXT_REL_POS.y, 50, BLACK);
    }
}