#include "Game.hpp"
#include "LevelState.hpp"
#include "components/Sprite.hpp"
#include "components/PlayerControlled.hpp"

void LevelState::onStart(Game &instance)
{
    instance.componentStorage.buildEntity()
            .withComponent(Sprite("player_ships", 0))
            .withComponent(Transform(Dimensional(10, 10), Dimensional(1, 1), Dimensional(1, 1)))
            .withComponent(PlayerControlled{})
            .build();
}

void LevelState::onPause(Game &instance)
{}

void LevelState::onResume(Game &instance)
{}

void LevelState::onTick(Game &instance)
{}

void LevelState::onStop(Game &instance)
{}
