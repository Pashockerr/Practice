#pragma once
#include "Sprite.h"
#include "Banknote.h"
#include "Button.h"
#include "Reciever.h"

namespace engine{
    class Terminal : public Sprite{
        public:
            Terminal(std::string texture_name, Vector2 pos, float rot, float scale, int layer, bool visible);
            void Tick(Scene*);
            void Draw();
        
        private:
            Reciever *reciever;
            Button *button_92;
            Button *button_95;
    };
}