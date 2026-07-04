#pragma once
#include "Sprite.h"
#include "Banknote.h"
#include "Button.h"
#include "Reciever.h"
#include "Label.h"
#include <list>

namespace engine
{
    enum State
    {
        GASOLINE_SELECT,
        AMOUNT_SELECT,
        WAIT_MONEY,
        FILLING,
        GIVE_CHANGE,
        PRINT_CHECK
    };

    class Terminal : public Sprite
    {
    public:
        Terminal(std::string texture_name, Vector2 pos, float rot, float scale, int layer, bool visible, Scene *scene);
        void Tick(Scene *);
        void Draw();

    private:
        float selected_litres;
        float received_money;
        float price_per_liter;
        State state;
        Label *label;
        Reciever *reciever;
        Sprite *helper;
        Sprite *nozzle_92;
        Sprite *nozzle_95;
        std::list<Button *> keyboard;
        void DisplayText(std::string);
    };
}