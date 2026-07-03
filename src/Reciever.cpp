#include "Reciever.h"
#include "Scene.h"
#include "Banknote.h"
#include <iostream>

namespace engine
{
    Reciever::Reciever(std::string texture_name, Vector2 pos, float rot, float scale, int layer, bool visible)
        : Sprite(texture_name, pos, rot, scale, layer, false, visible) {}

    void Reciever::Tick(Scene *scene)
    {
        for (auto it = scene->sprites.rbegin(); it != scene->sprites.rend(); it++)
        {
            auto sprite = *it;
            if (Banknote *banknote = dynamic_cast<Banknote*>(sprite))
            {
                if (CheckCollisionRecs(GetRectangle(), banknote->GetRectangle()) && recieving_banknote == nullptr)
                {
                    recieving_banknote = banknote;
                    banknote->StartRecievingAnimation(position);
                }
            }
        }
        if (recieving_banknote != nullptr && recieving_banknote->DoneRecievingAnimation())
        {
            recieving_banknote->visible = false;
            recieving_banknote->draggable = false;
            recieving_banknote->layer = -1;
            std::cout << "Recieved : " << recieving_banknote->value << std::endl;
            recieving_banknote = nullptr;
        }
    }
}