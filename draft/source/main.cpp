#include "Game.hpp"
#include "SfmlAudioModule.hpp"
#include "SfmlModule.hpp"
#include <iostream>

int main(void)
{
    Game game("R-Type SOLO");
    std::unique_ptr<IModule> sfml_module(new SfmlModule("R-Type SOLO v0.1"));
    auto audio_module = std::make_unique<SfmlAudioModule>();

    game.addModule("sfml", std::move(sfml_module));
    game.setDisplayModule("sfml");
    game.addModule("audio-sfml", std::move(audio_module));
    game.setAudioModule("audio-sfml");

    return 0;
}
