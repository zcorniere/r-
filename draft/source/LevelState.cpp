#include "Game.hpp"
#include "LevelState.hpp"
#include "components/Sprite.hpp"
#include "components/PlayerControlled.hpp"
#include "components/Velocity.hpp"

void LevelState::onStart(Game &instance)
{
    // Creating Back ground
    instance.componentStorage.buildEntity()
        .withComponent(Sprite("level1", 0))
        .withComponent(Transform(Dimensional(10, 10), Dimensional(1, 1), Dimensional(2, 2)))
        .withComponent(Velocity(-0.5, 0))
        .build();

    // Creating Player Ship
    instance.componentStorage.buildEntity()
        .withComponent(Sprite("player_ships", 0))
        .withComponent(Transform(Dimensional(10, 10), Dimensional(1, 1), Dimensional(1.5, 1.5)))
        .withComponent(PlayerControlled{1})
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
