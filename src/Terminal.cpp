#include "Terminal.h"

namespace engine
{
    const Vector2 B92_REL_POS{100, 100};
    const Vector2 B95_REL_POS{210, 100};
    const Vector2 RECIEVER_REL_POS{100, 210};
    const Vector2 TEXT_REL_POS{500, 500};

    Terminal::Terminal(std::string texture_name, Vector2 pos, float rot, float scale, int layer, bool visible)
        : Sprite(texture_name, pos, rot, scale, layer, false, visible)
    {

        button_92 = new engine::Button("resources/textures/button_inactive.png",
                                        "resources/textures/button_active.png",
                                        {pos.x + B92_REL_POS.x, pos.y + B92_REL_POS.y}, 0, 1, 0, true);
        button_95 = new engine::Button("resources/textures/button_inactive.png",
                                        "resources/textures/button_active.png",
                                        {pos.x + B95_REL_POS.x, pos.y + B95_REL_POS.y}, 0, 1, 0, true);
        reciever = new Reciever("resources/textures/port.png", {pos.x + RECIEVER_REL_POS.x, pos.y + RECIEVER_REL_POS.y},
                                0, .25f, 0, true);
    }

    void Terminal::Tick(Scene *scene)
    {
        button_92->Tick(scene);
        button_95->Tick(scene);
        reciever->Tick(scene);
    }

    void Terminal::Draw(){
        Sprite::Draw();
        button_92->Draw();
        button_95->Draw();
        reciever->Draw();

        DrawText(reciever->values.empty() ? "Didn't recieve" : std::to_string(reciever->values.front()).c_str()
            , position.x + TEXT_REL_POS.x, position.y + TEXT_REL_POS.y, 50, BLACK);
    }
}