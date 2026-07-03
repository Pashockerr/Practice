#include "../include/raylib.h"
#include "Scene.h"
#include "Banknote.h"
#include "Reciever.h"
#include "mouse_handler.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    engine::Scene scene(screenWidth, screenHeight, 61, "TEST");

    scene.Loop();

    return 0;
}

