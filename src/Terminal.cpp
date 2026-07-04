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
    const Vector2 NOZZLE_92_REL_POS{120, 0};
    const Vector2 NOZZLE_95_REL_POS{510, 0};
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
        total_litres = 0;
    }

    bool Terminal::AppropriateNozzleIsTaken()
    {
        return (!nozzle_92->visible && price_per_liter == constants::PRICE_92) || (!nozzle_95->visible && price_per_liter == constants::PRICE_95);
    }

    void Terminal::ComputeAndGiveChange()
    {
        received_money -= (total_litres - selected_litres) * price_per_liter;
        if (received_money < 50.0f)
        {
            state = State::GASOLINE_SELECT;
            return;
        }
        // Not so elegant cuz of floating point division errors
        while (received_money >= 5000.0f)
        {
            reciever->AddReturnValue(5000.0f);
            received_money -= 5000.0f;
        }
        while (received_money >= 1000.0f)
        {
            reciever->AddReturnValue(1000.0f);
            received_money -= 1000.0f;
        }
        while (received_money >= 500.0f)
        {
            reciever->AddReturnValue(500.0f);
            received_money -= 500.0f;
        }
        while (received_money >= 100.0f)
        {
            reciever->AddReturnValue(100.0f);
            received_money -= 100.0f;
        }
        while (received_money >= 50.0f)
        {
            reciever->AddReturnValue(50.0f);
            received_money -= 50.0f;
        }
        state = State::GIVE_CHANGE;
        reciever->ReturnChange();
    }

    void Terminal::Tick(Scene *scene)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            bool collides = false;
            for (auto sprite : scene->sprites)
            {
                if (Banknote *banknote = dynamic_cast<Banknote *>(sprite))
                {
                    if (banknote->MouseCollides())
                    {
                        collides = true;
                        break;
                    }
                }
            }
            if (nozzle_92->MouseCollides() && !collides)
            {
                nozzle_92->visible = !nozzle_92->visible;
            }
            if (nozzle_95->MouseCollides() && !collides)
            {
                nozzle_95->visible = !nozzle_95->visible;
            }
        }

        reciever->enabled = state == State::WAIT_MONEY;
        // Can't do anything if nozzle is not in place
        if (state == State::GASOLINE_SELECT || state == State::AMOUNT_SELECT || state == State::WAIT_MONEY)
        {
            if (!nozzle_92->visible || !nozzle_95->visible)
            {
                state = State::WAIT_NOZZLE;
            }
        }
        // Wait for nozzle to be returned
        if (state == State::WAIT_NOZZLE)
        {
            if (nozzle_92->visible && nozzle_95->visible)
            {
                if (!reciever->values.empty())
                {
                    state = State::WAIT_MONEY;
                }
                else if(selected_litres > 0){
                    state = State::AMOUNT_SELECT;
                }
                else
                {
                    ComputeAndGiveChange(); // If no change then just goes to first menu
                }
            }
        }

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
            if (received_money >= selected_litres * price_per_liter)
            {
                state = State::PAUSE_FILLING;
            }
        }

        // Process filling
        else if (state == State::FILLING)
        {
            if (AppropriateNozzleIsTaken())
            {
                selected_litres -= selected_litres > constants::FILLING_SPEED ? constants::FILLING_SPEED : constants::FILLING_SPEED - selected_litres;
                if (selected_litres <= 0)
                {
                    state = State::WAIT_NOZZLE;
                }
            }
            else
            {
                state = State::PAUSE_FILLING;
            }
        }

        // Renew filling if nozzle is appropriate again
        else if (state == State::PAUSE_FILLING)
        {
            if (AppropriateNozzleIsTaken())
            {
                state = State::FILLING;
            }
        }

        // Give change
        else if (state == State::GIVE_CHANGE && !reciever->IsReturningChange())
        {
            state = State::GASOLINE_SELECT;
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

                        total_litres = 0.0f;
                        selected_litres = 0.0f;
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
                        total_litres = selected_litres;
                        state = State::WAIT_MONEY;
                    }
                    if (key_code == 11)
                    {
                        if (selected_litres == 0)
                        {
                            state = State::GASOLINE_SELECT;
                        }
                        else
                        {
                            selected_litres = 0;
                        }
                    }
                }
                // Start waiting nozzle when enough money recieved and button pressed
                else if (state == State::WAIT_MONEY)
                {
                    if (key_code == 9 && !reciever->IsCurrentlyRecieving() && received_money >= selected_litres * price_per_liter)
                    {
                        state = State::PAUSE_FILLING;
                    }
                    // Return change if canceled
                    if (key_code == 11)
                    {
                        state = State::WAIT_NOZZLE;
                    }
                }
                // Give remaining change if filling is paused or nozzle
                else if (state == State::PAUSE_FILLING)
                {
                    if (key_code == 11)
                    {
                        state = State::WAIT_NOZZLE;
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
        case State::FILLING:
        case State::PAUSE_FILLING:
            label->text = "Filling...\n" + std::to_string(total_litres - selected_litres) + "/" + std::to_string(total_litres);
            break;
        case State::WAIT_NOZZLE:
            label->text = "Return nozzle";
            break;
        case State::GIVE_CHANGE:
            label->text = "Take change";
            break;
        default:
            label->text = "";
        }
    }
}