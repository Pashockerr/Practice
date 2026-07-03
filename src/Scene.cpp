#include "Scene.h"
#include "Sprite.h"
#include "Reciever.h"
#include "Banknote.h"
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

        sprites.push_front(new engine::Reciever("resources/textures/port.png", {700, 100}, 0, .25f, 0, true));

        sprites.push_front(new engine::Banknote("resources/textures/50.png", {100, 100}, 0, 2, 0, true));
        sprites.push_front(new engine::Banknote("resources/textures/100.png", {100, 100}, 0, 2, 0, true));
        sprites.push_front(new engine::Banknote("resources/textures/500.png", {100, 100}, 0, 2, 0, true));
        sprites.push_front(new engine::Banknote("resources/textures/1000.png", {100, 100}, 0, 2, 0, true));
        sprites.push_front(new engine::Banknote("resources/textures/5000.png", {100, 100}, 0, 2, 0, true));
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
            ClearBackground(RAYWHITE);
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