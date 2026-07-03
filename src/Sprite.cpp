#include "Sprite.h"

namespace engine{
    Sprite::Sprite(std::string texture_name, Vector2 pos, float rot, float scale, int layer, bool draggable, bool visible){
        this->texture = LoadTexture(texture_name.c_str());
        this->position = pos;
        this->rotation = rot;
        this->scale = scale;
        this->layer = layer;
        this->draggable = draggable;
        this->visible = visible;
    }

    void Sprite::Draw(){
        if(!visible) return;
        DrawTextureEx(this->texture, this->position, this->rotation, this->scale, WHITE);
        // Debug renderer
        DrawRectangleLinesEx(this->GetRectangle(), 1, RED);
    }
    
    void Sprite::ChangeTexture(std::string texture_name){
        UnloadTexture(this->texture);
        this->texture = LoadTexture(texture_name.c_str());
    }
    
    void Sprite::ChangeTexture(Texture2D texture){
        UnloadTexture(this->texture);
        this->texture = texture;
    }

    void Sprite::SetScale(float scale){
        if(scale > 0){
            this->scale = scale;
        }
    }

    float Sprite::GetScale(){
        return this->scale;
    }
    
    Rectangle Sprite::GetRectangle(){
        return {position.x, position.y, (float)texture.width*scale, (float)texture.height*scale};
    }

    Sprite::~Sprite(){
        //UnloadTexture(this->texture);
    }

    bool Sprite::MouseCollides(){
        return CheckCollisionPointRec(GetMousePosition(), GetRectangle());
    }

    void Sprite::Tick(Scene *scene){

    }
}