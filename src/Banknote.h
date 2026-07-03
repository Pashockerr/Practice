#pragma once
#include "Sprite.h"

namespace engine
{
    class Banknote : public Sprite
    {
    public:
        Banknote(std::string texture_name, Vector2 pos, float rot, float scale, int layer, bool visible, float value);
        void Tick(Scene *);
        void StartRecievingAnimation(Vector2);
        bool DoneRecievingAnimation();
        float value;
        float GetRemainingLength();

    private:
        Vector2 recieve_anchor;
    };
}