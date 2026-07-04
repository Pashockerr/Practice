#include "../include/raylib.h"
#include "Scene.h"
#include "Banknote.h"
#include "Reciever.h"
#include "mouse_handler.h"
#include "constants.h"

int main(void)
{
    engine::Scene scene(constants::SCREEN_WIDTH, constants::SCREEN_HEIGHT, 60, "Gas station");
    scene.Loop();
    return 0;
}

