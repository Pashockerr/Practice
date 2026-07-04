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
            bool IsCurrentlyRecieving();
            void AddReturnValue(float value);
            float PopReturnValue();
            void ClearReturnValues();
            void ReturnChange();
            bool IsReturningChange();

        private:
            Banknote *recieving_banknote;
            Banknote *returning_banknote;
            std::list<float> return_values;
            bool is_returning_change;
    };
}