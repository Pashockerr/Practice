#pragma once
#include "Sprite.h"

namespace engine{
    class Label : public Sprite{
        public:
            Label(std::string text, int font_size, Vector2 pos, float rot, float scale, int layer, bool visible);
            std::string text;
            void Draw();
            int GetFontSize();
            void SetFontSize(int);
        private:
            int font_size;
            Font font;
    };
}