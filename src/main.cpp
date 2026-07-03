#include "../include/raylib.h"
#include "Scene.h"
#include "Banknote.h"
#include "Reciever.h"
#include "mouse_handler.h"

int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    engine::Scene scene(screenWidth, screenHeight, 61, "TEST");

    scene.Loop();

    return 0;
}

