#include "Terminal.h"

namespace engine{
    Terminal::Terminal(std::string texture_name, Vector2 pos, float rot, float scale, int layer, bool visible)
    : Sprite(texture_name, pos, rot, scale, layer, false, visible){
    }

    void Terminal::Tick(Scene *scene){

    }
}