#pragma once
#include <list>
#include <string>
#include "../include/raylib.h"

namespace engine
{
    class Sprite;
    class Scene
    {
    public:
        std::list<Sprite*> sprites;
        Scene(int width, int height, int fps, std::string window_name);
        ~Scene();
        void Loop();
        void QueueReorder();
        Texture texture_5000;
        Texture texture_1000;
        Texture texture_500;
        Texture texture_100;
        Texture texture_50;
        
    private:
        void Tick();
        bool need_reorder;
    };
}