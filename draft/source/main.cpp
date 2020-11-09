#include "Game.hpp"
#include "SfmlAudioModule.hpp"
#include "SfmlModule.hpp"
#include <iostream>

class BasicState : public AState {
public:
    void onStart(Game &instance) {}
    void onPause(Game &instance) {}
    void onResume(Game &instance) {}
    void onTick(Game &instance) {}
    void onStop(Game &instance) {}
};

int main(void)
{
    Game game("R-Type SOLO");
    std::unique_ptr<IModule> sfml_module(new SfmlModule("R-Type SOLO v0.1"));
    std::unique_ptr<AState> state(new BasicState);
    auto audio_module = std::make_unique<SfmlAudioModule>();

    game.addModule("sfml", std::move(sfml_module));
    game.setDisplayModule("sfml");
    game.addModule("audio-sfml", std::move(audio_module));
    game.setAudioModule("audio-sfml");

    game.stateMachine.setState(std::move(state));

    game.run();
}
