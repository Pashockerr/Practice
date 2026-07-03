#pragma once
#include <string>
#include "../include/raylib.h"

namespace engine
{
    class Scene;
    class Sprite
    {
    public:
        Sprite(std::string texture_name, Vector2 pos, float rot, float scale, int layer, bool draggable, bool visible);
        ~Sprite();
        void Draw();
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
        virtual void Tick(Scene*);
    private:
        Texture2D texture;
        float scale;
    };
}