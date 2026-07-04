#pragma once
#include "Sprite.h"
#include "Banknote.h"
#include <list>

namespace engine{
    class Reciever : public Sprite{
        public:
            Reciever(std::string texture_name, Vector2 pos, float rot, float scale, int layer, bool visible);
            void Tick(Scene*);
            std::list<float> values;
            bool enabled;

        private:
            Banknote *recieving_banknote;
    };
}