#include "Banknote.h"
#include "constants.h"
#include "Scene.h"
#include <iostream>

namespace engine{
    Banknote::Banknote(std::string texture_name, Vector2 pos, float rot, float scale, int layer, bool visible, float value) 
    : Sprite(texture_name, pos, rot, scale, layer, true, visible){
        this->value = value;
        recieve_anchor = { -1, -1 };
    }

    float Banknote::GetRemainingLength(){
        return position.y - (recieve_anchor.y - GetRectangle().height);
    }

    void Banknote::Tick(Scene *scene){
        if(GetRemainingLength() >= 0 && recieve_anchor.y >= 0){
            draggable = false;
            position.y -= constants::RECIEVING_SPEED;
            position.x = recieve_anchor.x;
        }
    }

    void Banknote::StartRecievingAnimation(Vector2 pos){
        position = pos;
        recieve_anchor = pos;
    }

    bool Banknote::DoneRecievingAnimation(){
        return GetRemainingLength() < 0;
    }
}