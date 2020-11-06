#include "Game.hpp"
#include "SfmlModule.hpp"
#include <iostream>

int main(void)
{
    Game game("R-Type SOLO");
    std::unique_ptr<IModule> sfml_module(new SfmlModule("R-Type SOLO v0.1"));

    game.addModule("sfml", std::move(sfml_module));
    game.setDisplayModule("sfml");

    return 0;
}
