#pragma once
#include "Sprite.h"
#include "Banknote.h"
#include "Button.h"
#include "Reciever.h"
#include <list>

namespace engine{
    class Terminal : public Sprite{
        public:
            Terminal(std::string texture_name, Vector2 pos, float rot, float scale, int layer, bool visible, Scene *scene);
            void Tick(Scene*);
            void Draw();
        
        private:
            Reciever *reciever;
            Sprite *helper;
            std::list<Button*> keyboard;
    };
}