#include "Terminal.h"
#include <math.h>
#include <iostream>
#include "Scene.h"
#include "constants.h"

namespace engine
{
    const Vector2 RECIEVER_REL_POS{870, 610};
    const Vector2 TEXT_REL_POS{810, 30};
    const Vector2 KEYBOARD_REL_POS{870, 170};
    const Vector2 HELPER_REL_POS{780, 0};
    const Vector2 NOZZLE_92_REL_POS {120, 0};
    const Vector2 NOZZLE_95_REL_POS {510, 0};
    const int FONT_SIZE = 30;
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

        nozzle_92 = new Sprite("resources/textures/nozzle_92.png", {pos.x + NOZZLE_92_REL_POS.x, pos.y + HELPER_REL_POS.y},
                            0, 1, 1, false, true);
        scene->sprites.push_front(nozzle_92);
        
        nozzle_95 = new Sprite("resources/textures/nozzle_95.png", {pos.x + NOZZLE_95_REL_POS.x, pos.y + HELPER_REL_POS.y},
                            0, 1, 1, false, true);
        scene->sprites.push_front(nozzle_95);

        label = new Label("", 30, {position.x + TEXT_REL_POS.x, position.y + TEXT_REL_POS.y},
                          0, 1, 2, true);
        scene->sprites.push_front(label);

        for (int i = 0; i < 12; i++)
        {
            auto button = new engine::Button("resources/textures/button_inactive.png",
                                             "resources/textures/button_active.png",
                                             {pos.x + KEYBOARD_REL_POS.x + (i % 3) * BUTTON_SIDE + (i % 3) * KEYBOARD_MARGIN,
                                              pos.y + KEYBOARD_REL_POS.y + (float)std::floor(i / 3) * BUTTON_SIDE + (float)std::floor(i / 3) * KEYBOARD_MARGIN},
                                             0, 1, 2, true);
            keyboard.push_back(button);
            scene->sprites.push_front(button);
        }

        state = State::GASOLINE_SELECT;
        selected_litres = 0;
        received_money = 0;
        price_per_liter = 0;
    }

    void Terminal::Tick(Scene *scene)
    {
        // Recieve money
        if (state == State::WAIT_MONEY)
        {
            if (!reciever->values.empty())
            {
                for (float value : reciever->values)
                {
                    received_money += value;
                }
                reciever->values.clear();
            }
        }

        int key_code = 0;
        for (auto it = keyboard.begin(); it != keyboard.end(); it++)
        {
            auto button = *it;
            if (button->IsClicked())
            {
                // Gasoline select
                if (state == State::GASOLINE_SELECT)
                {
                    if (key_code == 0 || key_code == 1)
                    {
                        price_per_liter = key_code ? constants::PRICE_95 : constants::PRICE_92;
                        state = State::AMOUNT_SELECT;
                    }
                }
                // Amount select
                else if (state == State::AMOUNT_SELECT)
                {
                    if (key_code >= 0 && key_code < 9 || key_code == 10)
                    {
                        selected_litres *= 10;
                        selected_litres += key_code == 10 ? 0 : (key_code + 1) % 10;
                    }
                    if (key_code == 9 && selected_litres > 0)
                    {
                        state = State::WAIT_MONEY;
                        reciever->enabled = true;
                    }
                }
            }
            key_code++;
        }
    }

    void Terminal::Draw()
    {
        Sprite::Draw();

        switch (state)
        {
        case State::GASOLINE_SELECT:
            label->text = "Select gasoline: \n1 - 92   2 - 95";
            break;
        case State::AMOUNT_SELECT:
            label->text = "Input litres: \n" + std::to_string(selected_litres);
            break;
        case State::WAIT_MONEY:
            label->text = "Insert money: \n" + std::to_string(received_money) + "/" + std::to_string(selected_litres * price_per_liter);
            break;
        default:
            label->text = "";
        }
    }
}