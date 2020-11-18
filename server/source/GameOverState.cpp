#include "Game.hpp"
#include "GameOverState.hpp"
#include "components/Sprite.hpp"
#include "components/Transform.hpp"
#include "components/Velocity.hpp"
#include "components/Lifetime.hpp"
#include "components/DeathRattle.hpp"
#include "LobbyState.hpp"

void GameOverState::onStart(Game &instance)
{
    instance.audioModule.value().get().playSound("game_over", 1, 1, true);

    instance.componentStorage.buildEntity()
        .withComponent(Sprite("space_background", 0))
        .withComponent(Transform({0,0}, {0,0}, {1800, 960}))
        .build();

    instance.componentStorage.buildEntity()
        .withComponent(Sprite("menus", 20))
        .withComponent(Transform({487.5, 392.5}, {0, 0}, {5, 5}))
        .withComponent(Lifetime(1000))
        .withComponent(DeathRattle([](Game &instance){
            std::unique_ptr<AState> state(new LobbyState);

            instance.stateMachine.setState(std::move(state));
        }))
        .build();
}

void GameOverState::onPause(Game &instance)
{}

void GameOverState::onResume(Game &instance)
{}

void GameOverState::onTick(Game &instance)
{}

void GameOverState::onStop(Game &instance)
{
    instance.audioModule.value().get().stopSound("game_over");
}
