#include "Game.hpp"
#include "LobbyState.hpp"
#include "components/Sprite.hpp"
#include "components/PlayerShipController.hpp"
#include "components/Velocity.hpp"
#include "components/CollisionBox.hpp"
#include "components/GameObject.hpp"
#include "components/PatternLoop.hpp"
#include "components/AnimationLoop.hpp"
#include "components/Destructible.hpp"
#include "components/AnimMontage.hpp"
#include "components/WaveCannon.hpp"
#include "components/Trajectory.hpp"
#include "components/BydoShooter.hpp"
#include "components/PlayerScanner.hpp"
#include "components/RestrictionBox.hpp"
#include "components/EnemyGroup.hpp"
#include "components/Speaker.hpp"
#include "components/PlayerBarracks.hpp"
#include "components/BackgroundMusic.hpp"
#include "components/WormHole.hpp"
#include "Enemies.hpp"
#include "load_game.hpp"
#include "LevelState.hpp"
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <cmath>
#include <memory>
#include <functional>

// Counted in milleseconds
constexpr int STAR_SPAWN_DELAY = 250;

constexpr unsigned STAR_BUFFER_SIZE = 50;

constexpr float SCROLLING_SPEED = 0.5;

void LobbyState::onStart(Game &instance)
{
    instance.componentStorage.buildEntity()
        .withComponent(Sprite("space_background", 0))
        .withComponent(Transform({0,0}, {0,0}, {1800, 960}))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Sprite("menus", 0))
        .withComponent(Transform({556.5, -100}, {0, 0}, {1, 1}))
        .withComponent(Trajectory{[](Transform &t) {
            if (t.location.y < 100)
                t.location.y++;
        }})
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Sprite("menus", 10))
        .withComponent(Transform({1700, 200}, {0, 0}, {4, 4}))
        .withComponent(AnimationLoop({
            {"menus", 10}, {"menus", 11}}, 50)
        )
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Sprite("menus", 10))
        .withComponent(Transform({1700, 724}, {0, 0}, {4, 4}))
        .withComponent(AnimationLoop({
            {"menus", 10}, {"menus", 11}}, 50)
        )
        .build();
    int barracks_id = instance.componentStorage.buildEntity()
        .withComponent(PlayerBarracks(true, true))
        .build();

    instance.componentStorage.buildEntity()
        .withComponent(BackgroundMusic{"title", 0.7})
        .build();

    instance.componentStorage.buildEntity()
        .withComponent(Transform({1900, 0}, {0, 0}, {1, 1}))
        .withComponent(CollisionBox(100, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(WormHole(barracks_id))
        .build();
}

void LobbyState::onPause(Game &instance)
{}

void LobbyState::onResume(Game &instance)
{}

void LobbyState::onTick(Game &instance)
{
    static std::chrono::time_point last_update = std::chrono::system_clock::now();
    std::chrono::milliseconds tick_delay(STAR_SPAWN_DELAY);

    if (std::chrono::system_clock::now() - last_update < tick_delay)
        return;
    last_update = std::chrono::system_clock::now();

    float scale = rand() % 4 + 3;
    float height = rand() % 1000;
    float speed = rand() % 5 + 1;

    m_stars_ids.push(
        instance.componentStorage.buildEntity()
            .withComponent(Sprite("player_ships", 50))
            .withComponent(Transform(Dimensional(2000, height), Dimensional(0, 0), Dimensional(scale, scale)))
            .withComponent(Velocity(-1 * speed, 0))
            .build()
    );
    while (m_stars_ids.size() > STAR_BUFFER_SIZE) {
        instance.componentStorage.destroyEntity(m_stars_ids.front());
        m_stars_ids.pop();
    }
}

void LobbyState::onStop(Game &instance)
{}
