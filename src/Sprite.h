#pragma once
#include <string>
#include "../include/raylib.h"

/*
    Layers: 
    -1 - inactive
    0 - background, obeyed banknotes
    1 - helper sprites
    2 - buttons, interface, inactive draggables
    3 - active draggables
*/


namespace engine
{
    class Scene;
    class Sprite
    {
    public:
        Sprite(std::string texture_name, Vector2 pos, float rot, float scale, int layer, bool draggable, bool visible);
        Sprite(Texture texture, Vector2 pos, float rot, float scale, int layer, bool draggable, bool visible);
        ~Sprite();
        virtual void Draw();
        void ChangeTexture(std::string texture_name);
        void ChangeTexture(Texture2D texture);
        void SetScale(float scale);
        float GetScale();
        Rectangle GetRectangle();
        Vector2 position;
        float rotation;
        int layer;
        bool draggable;
        bool visible;
        bool MouseCollides();
        bool is_being_dragged;
        virtual void Tick(Scene*);

    private:
        float scale;

    protected:
        Texture2D texture;
    };
}