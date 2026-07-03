#pragma once
#include <list>
#include <string>

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
    private:
        void Tick();
        bool need_reorder;
    };
}