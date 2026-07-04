#include "Banknote.h"
#include "constants.h"
#include "Scene.h"
#include <iostream>

namespace engine{
    Banknote::Banknote(std::string texture_name, Vector2 pos, float rot, float scale, int layer, bool visible, float value) 
    : Sprite(texture_name, pos, rot, scale, layer, true, visible){
        this->value = value;
        recieve_anchor = { -1, -1 };
        return_anchor = { -1, -1 };
    }

    Banknote::Banknote(Texture texture, Vector2 pos, float rot, float scale, int layer, bool visible, float value) 
    : Sprite(texture, pos, rot, scale, layer, true, visible){
        this->value = value;
        recieve_anchor = { -1, -1 };
        return_anchor = { -1, -1 };
    }

    float Banknote::GetRemainingLength(){
        return position.y - (recieve_anchor.y - GetRectangle().height);
    }

    float Banknote::GetRemainingReturnLength(){
        return return_anchor.y - position.y;
    }

    void Banknote::Tick(Scene *scene){
        if(GetRemainingLength() >= 0 && recieve_anchor.y >= 0 && !draggable){
            position.y -= constants::RECIEVING_SPEED;
            position.x = recieve_anchor.x;
        }

        if(GetRemainingReturnLength() >= 0 && return_anchor.y >= 0 && !draggable){
            position.y += constants::RECIEVING_SPEED;
            position.x = return_anchor.x;
        }
    }

    void Banknote::StartRecievingAnimation(Vector2 pos){
        position = pos;
        recieve_anchor = pos;
    }

    void Banknote::StartReturningAnimation(Vector2 pos){
        position = { pos.x, pos.y - GetRectangle().height };
        return_anchor = pos;
    }

    bool Banknote::DoneRecievingAnimation(){
        bool res = GetRemainingLength() < 0;
        if(res){
            recieve_anchor = { -1, -1 };
        }
        return res;
    }

    bool Banknote::DoneReturningAnimation(){
        bool res = GetRemainingReturnLength() < 0;
        if(res){
            return_anchor = { -1, -1 };
        }
        return res;
    }
}