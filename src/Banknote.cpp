#include "Banknote.h"

namespace engine{
    Banknote::Banknote(std::string texture_name, Vector2 pos, float rot, float scale, int layer, bool visible) 
    : Sprite(texture_name, pos, rot, scale, layer, true, visible){
    }

    void Banknote::Tick(Scene *scene){

    }
}