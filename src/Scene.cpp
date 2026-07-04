#include "Scene.h"
#include "Sprite.h"
#include "Reciever.h"
#include "Banknote.h"
#include "Button.h"
#include "Terminal.h"
#include <iostream>
#include "../include/raylib.h"
#include "mouse_handler.h"

namespace engine
{
    void Scene::Tick()
    {
        engine::handle_mouse(this);
    }

    Scene::Scene(int width, int height, int fps, std::string window_name)
    {
        InitWindow(width, height, window_name.c_str());
        SetTargetFPS(fps);
        this->need_reorder = true;

        sprites.push_front(new engine::Banknote("resources/textures/50.png", {500, 500}, 0, 2, 2, true, 50));
        sprites.push_front(new engine::Banknote("resources/textures/100.png", {500, 500}, 0, 2, 2, true, 100));
        sprites.push_front(new engine::Banknote("resources/textures/500.png", {500, 500}, 0, 2, 2, true, 500));
        sprites.push_front(new engine::Banknote("resources/textures/1000.png", {500, 500}, 0, 2, 2, true, 1000));
        sprites.push_front(new engine::Banknote("resources/textures/5000.png", {500, 500}, 0, 2, 2, true, 5000));

        sprites.push_front(new engine::Terminal("resources/textures/terminal.png", {0, 0}, 0, 1, 0, true, this));
    }

    Scene::~Scene()
    {
        CloseWindow();
    }

    void Scene::Loop()
    {
        while (!WindowShouldClose())
        {
            Tick();
            for (auto sprite : sprites)
            {
                sprite->Tick(this);
            }
            if (this->need_reorder)
            {
                this->sprites.sort([](Sprite *a, Sprite *b)
                                   { return a->layer < b->layer; });
                this->need_reorder = false;
            }
            BeginDrawing();
            ClearBackground({ 51, 51, 51, 255 });
            for (auto sprite : sprites)
            {
                sprite->Draw();
            }
            EndDrawing();
        }
    }

    void Scene::QueueReorder()
    {
        this->need_reorder = true;
    }
}