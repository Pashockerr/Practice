#include "Reciever.h"
#include "Scene.h"
#include "Banknote.h"
#include <iostream>

namespace engine
{
    Reciever::Reciever(std::string texture_name, Vector2 pos, float rot, float scale, int layer, bool visible)
        : Sprite(texture_name, pos, rot, scale, layer, false, visible)
    {
        recieving_banknote = nullptr;
        returning_banknote = nullptr;
        is_returning_change = false;
    }

    float Reciever::PopReturnValue()
    {
        if (!return_values.empty())
        {
            float val = return_values.front();
            return_values.pop_front();
            return val;
        }
        else
        {
            return 0;
        }
    }

    void Reciever::ClearReturnValues()
    {
        return_values.clear();
    }

    void Reciever::AddReturnValue(float value)
    {
        if (value == 50.0f || value == 100.0f || value == 500.0f || value == 1000.0f || value == 5000.0f)
        {
            return_values.push_back(value);
        }
    }

    void Reciever::Tick(Scene *scene)
    {
        if (is_returning_change && returning_banknote == nullptr)
        {
            float return_val = PopReturnValue();
            Banknote *banknote = nullptr;

            if (return_val == 50.0f)
            {
                banknote = new Banknote(scene->texture_50, {position.x, position.y - scene->texture_50.height}, 0, 2, 0, true, 50);
            }
            else if (return_val == 100.0f)
            {
                banknote = new Banknote(scene->texture_100, {position.x, position.y - scene->texture_100.height}, 0, 2, 0, true, 50);
            }
            else if (return_val == 500.0f)
            {
                banknote = new Banknote(scene->texture_500, {position.x, position.y - scene->texture_500.height}, 0, 2, 0, true, 50);
            }
            else if (return_val == 1000.0f)
            {
                banknote = new Banknote(scene->texture_1000, {position.x, position.y - scene->texture_1000.height}, 0, 2, 0, true, 50);
            }
            else if (return_val == 5000.0f)
            {
                banknote = new Banknote(scene->texture_5000, {position.x, position.y - scene->texture_5000.height}, 0, 2, 0, true, 50);
            }

            if(banknote == nullptr){
                is_returning_change = false;
                return;
            }

            returning_banknote = banknote;
            banknote->StartReturningAnimation(position);
            banknote->draggable = false;

            scene->sprites.push_back(returning_banknote);
            scene->QueueReorder();
        }

        if (returning_banknote != nullptr)
        {
            enabled = false;
            if (returning_banknote->DoneReturningAnimation())
            {
                returning_banknote->draggable = true;
                returning_banknote->layer = 2;
                returning_banknote = nullptr;
            }
        }

        if (recieving_banknote != nullptr)
        {
            if (recieving_banknote->DoneRecievingAnimation())
            {
                recieving_banknote->visible = false;
                recieving_banknote->draggable = false;
                recieving_banknote->layer = -1;
                values.push_front(recieving_banknote->value);
                recieving_banknote = nullptr;
            }
        }

        if (!enabled)
            return;

        for (auto it = scene->sprites.rbegin(); it != scene->sprites.rend(); it++)
        {
            auto sprite = *it;
            if (Banknote *banknote = dynamic_cast<Banknote *>(sprite))
            {
                if (CheckCollisionRecs(GetRectangle(), banknote->GetRectangle()) && recieving_banknote == nullptr && !banknote->is_being_dragged)
                {
                    recieving_banknote = banknote;
                    banknote->StartRecievingAnimation(position);
                    banknote->layer = 0;
                    banknote->draggable = false;
                    scene->QueueReorder();
                }
            }
        }
    }

    void Reciever::ReturnChange()
    {
        if (!IsCurrentlyRecieving()){
            enabled = false;
            is_returning_change = true;
        }
            
    }

    bool Reciever::IsCurrentlyRecieving()
    {
        return recieving_banknote != nullptr;
    }

    bool Reciever::IsReturningChange(){
        return is_returning_change;
    }
}