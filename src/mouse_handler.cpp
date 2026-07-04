#include "mouse_handler.h"
#include "../include/raylib.h"
#include "Sprite.h"
#include <iostream>

namespace engine{
    Sprite *dragging_sprite_p = nullptr;
    Vector2 drag_offset;

    void handle_mouse(Scene *scene){
        if(dragging_sprite_p != nullptr && !dragging_sprite_p->draggable){
            dragging_sprite_p->is_being_dragged = false;
            dragging_sprite_p = nullptr;
            return;
        }

        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            if(dragging_sprite_p == nullptr){
                for(auto it = scene->sprites.rbegin(); it != scene->sprites.rend(); ++it){
                    Sprite *sprite_p = *it;
                    if(!sprite_p->draggable)
                        continue;
                    if(CheckCollisionPointRec(GetMousePosition(), sprite_p->GetRectangle())){
                        if(dragging_sprite_p == nullptr)
                            dragging_sprite_p = sprite_p;
                            dragging_sprite_p->layer = 3;
                            scene->QueueReorder();
                            continue;
                        if(dragging_sprite_p != nullptr && sprite_p->layer >= dragging_sprite_p->layer)
                            dragging_sprite_p = sprite_p;
                    }
                }
            }
            if(dragging_sprite_p != nullptr){
                dragging_sprite_p->is_being_dragged = true;
            }
        }
        if(IsMouseButtonUp(MOUSE_BUTTON_LEFT)){
            if(dragging_sprite_p != nullptr){
                dragging_sprite_p->layer = 2;
                dragging_sprite_p->is_being_dragged = false;
                dragging_sprite_p = nullptr;
                scene->QueueReorder();
            }
        }

        if(dragging_sprite_p != nullptr && dragging_sprite_p->draggable){
            auto m_d = GetMouseDelta();
            dragging_sprite_p->position.x += m_d.x;
            dragging_sprite_p->position.y += m_d.y;
        }
    }
}