#pragma once
#include "Sprite.h"

namespace engine{
    class Banknote : public Sprite{
        public:
        Banknote(std::string texture_name, Vector2 pos, float rot, float scale, int layer, bool visible);
        void Tick(Scene*);
    };
}