#pragma once
#include "Sprite.h"

namespace engine{
    class Terminal : public Sprite{
        public:
            Terminal(std::string texture_name, Vector2 pos, float rot, float scale, int layer, bool visible);
            void Tick(Scene*);
    };
}