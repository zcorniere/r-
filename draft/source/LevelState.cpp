#include "Game.hpp"
#include "LevelState.hpp"
#include "components/Sprite.hpp"
#include "components/PlayerControlled.hpp"
#include "components/Velocity.hpp"
#include "components/CollisionBox.hpp"
#include "components/GameObject.hpp"
#include <iostream>

void LevelState::onStart(Game &instance)
{
    // Creating Back ground
    instance.componentStorage.buildEntity()
        .withComponent(Sprite("level1", 0))
        .withComponent(Transform(Dimensional(10, 10), Dimensional(0, 0), Dimensional(2, 2)))
        .withComponent(Velocity(-0.5, 0))
        .build();

    // Creating Player Ship
    instance.componentStorage.buildEntity()
        .withComponent(Sprite("player_ships", 2))
        .withComponent(Transform(Dimensional(10, 10), Dimensional(0, 0), Dimensional(1.5, 1.5)))
        .withComponent(PlayerControlled{1})
        .withComponent(GameObject::PlayerShip)
        .withComponent(CollisionBox(30, 10, [](GameObject object){ std::cout << "gmal\n"; }, 0, 5))
        .build();

    // Floor CollisionBox
    instance.componentStorage.buildEntity()
        .withComponent(Transform(Dimensional(0, 460), Dimensional(1, 1), Dimensional(1, 1)))
        .withComponent(GameObject::Wall)
        .withComponent(CollisionBox(1000, 30))
        .build();

    // Example Projectile
    instance.componentStorage.buildEntity()
        .withComponent(Sprite("player_projectiles", 2))
        .withComponent(Transform(Dimensional(0, 200), Dimensional(0, 0), Dimensional(1, 1)))
        .withComponent(Velocity(7, 0))
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
