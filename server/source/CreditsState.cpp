#include "Game.hpp"
#include "CreditsState.hpp"
#include "components/Sprite.hpp"
#include "components/Transform.hpp"
#include "components/Velocity.hpp"
#include "components/Lifetime.hpp"
#include "components/DeathRattle.hpp"
#include "LobbyState.hpp"

void CreditsState::onStart(Game &instance)
{
    instance.audioModule.value().get().playSound("credits", 1, 1, true);

    instance.componentStorage.buildEntity()
        .withComponent(Sprite("space_background", 0))
        .withComponent(Transform({0,0}, {0,0}, {1800, 960}))
        .build();

    instance.componentStorage.buildEntity()
        .withComponent(Sprite("credits", 0))
        .withComponent(Transform({160, 1000}, {0, 0}, {5, 5}))
        .withComponent(Velocity({0, -0.3}))
        .withComponent(Lifetime(10000))
        .withComponent(DeathRattle([](Game &instance){
            std::unique_ptr<AState> state(new LobbyState);

            instance.stateMachine.setState(std::move(state));
        }))
        .build();
}

void CreditsState::onPause(Game &instance)
{}

void CreditsState::onResume(Game &instance)
{}

void CreditsState::onTick(Game &instance)
{}

void CreditsState::onStop(Game &instance)
{
    instance.audioModule.value().get().stopSound("credits");
}
