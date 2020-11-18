#include "Game.hpp"
#include "LevelState.hpp"
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
#include "components/BackgroundMusic.hpp"
#include "components/PlayerBarracks.hpp"
#include "components/Paralyzed.hpp"
#include "Enemies.hpp"
#include "load_game.hpp"
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <cmath>

// Counted in milleseconds
constexpr int STAR_SPAWN_DELAY = 250;

constexpr unsigned STAR_BUFFER_SIZE = 200;

constexpr float SCROLLING_SPEED = 50;

constexpr float SCROLLING_TICKS = (4028 * 4 - 1900) / SCROLLING_SPEED;

LevelState::LevelState(std::vector<bool> players) : m_players(players), m_stars_ids(), AState()
{}

void LevelState::onStart(Game &instance)
{
    // Creating Back ground
    instance.componentStorage.buildEntity()
        .withComponent(Sprite("level1", 0))
        .withComponent(Transform(Dimensional(10, 10), Dimensional(0, 0),
                                 Dimensional(4, 4)))
        .withComponent(Velocity(-1 * SCROLLING_SPEED, 0))
        .withComponent(Paralyzed(0, SCROLLING_TICKS, true))
        .build();

    int barracks_id = instance.componentStorage.buildEntity()
        .withComponent(PlayerBarracks(false, false, m_players))
        .build();

    // Floor CollisionBox
    instance.componentStorage.buildEntity()
        .withComponent(Transform(Dimensional(0, 920), Dimensional(1, 1),
                                 Dimensional(1, 1)))
        .withComponent(GameObject::Wall)
        .withComponent(CollisionBox(2000, 60, 0, 0, 1000))
        .build();

    std::string no_enemies((getenv("RTYPE_NO_ENEMIES"))? getenv("RTYPE_NO_ENEMIES") : "false");

    if (no_enemies != "true") {
        // Bugs Enemies
        instance.componentStorage.buildEntity()
            .withBuilder(Enemy::BUG)
            .withComponent(Transform({2000, 400}, {0, 0}, {3, 3}))
            .withComponent(BydoShooter())
            .withComponent(PlayerScanner(2000))
            .build();

        // Example Enemy group
        instance.componentStorage.buildEntity()
            .withComponent(EnemyGroup{Enemy::PATA_PATA, 10, 60})
            .withComponent(Transform({2000, 400}, {0, 0}, {3, 3}))
            .withComponent(Destructible{0})
            .build();

        }

    // Final Boss
    instance.componentStorage.buildEntity()
        .withComponent(Sprite("dobkeratops", 0))
        .withComponent(Transform({3861 * 4, 20 * 4}, {0, 0}, {4, 4}))
        .withComponent(Velocity(-1 * SCROLLING_SPEED, 0))
        .withComponent(Paralyzed(0, SCROLLING_TICKS, true))
        .withComponent(AnimationLoop({{
        {"dobkeratops", 2}, {"dobkeratops", 2}, {"dobkeratops", 2}, {"dobkeratops", 2},
        {"dobkeratops", 2}, {"dobkeratops", 2}, {"dobkeratops", 2}, {"dobkeratops", 2},
        {"dobkeratops", 1}, {"dobkeratops", 0}, {"dobkeratops", 0}, {"dobkeratops", 1},
        {"dobkeratops", 0}, {"dobkeratops", 1}, {"dobkeratops", 0}, {"dobkeratops", 0}
        }, 13}))
        .build();

    // Playing music
    instance.componentStorage.buildEntity()
        .withComponent(BackgroundMusic{"stage-1", 0.7})
        .build();
    // Turrets
    auto place_ennemy = [&](const Enemy &enemy, Dimensional pos) {
        instance.componentStorage.buildEntity()
            .withBuilder(enemy)
            .withComponent(Velocity{-1 * SCROLLING_SPEED, 0})
            .withComponent(
                Transform{{pos.x * 4 + 3, pos.y * 4 + 2}, {0, 0}, {4, 4}})
            .build();
    };
    // Group 1
    place_ennemy(Enemy::TURRET_UP, {1881, 47});
    place_ennemy(Enemy::TURRET_UP, {1852, 47});
    place_ennemy(Enemy::TURRET_UP, {1821, 32});
    place_ennemy(Enemy::TURRET_UP, {1788, 32});
    place_ennemy(Enemy::TURRET_DOWN, {1881, 179});
    place_ennemy(Enemy::TURRET_DOWN, {1852, 179});
    place_ennemy(Enemy::TURRET_DOWN, {1821, 195});
    place_ennemy(Enemy::TURRET_DOWN, {1788, 195});
    // Group 2
    place_ennemy(Enemy::TURRET_UP, {2491, 31});
    place_ennemy(Enemy::TURRET_UP, {2523, 31});
    place_ennemy(Enemy::TURRET_UP, {2553, 15});
    place_ennemy(Enemy::TURRET_UP, {2585, 15});
    place_ennemy(Enemy::TURRET_UP, {2617, 15});
    place_ennemy(Enemy::TURRET_UP, {2650, 15});
    place_ennemy(Enemy::TURRET_UP, {2681, 15});
    place_ennemy(Enemy::TURRET_UP, {2714, 15});
    // Group 3
    place_ennemy(Enemy::TURRET_UP, {2810, 47});
    place_ennemy(Enemy::TURRET_UP, {2842, 47});
    // Group 4
    place_ennemy(Enemy::TURRET_UP, {3162, 15});
    place_ennemy(Enemy::TURRET_UP, {3194, 15});
    place_ennemy(Enemy::TURRET_UP, {3226, 15});
    place_ennemy(Enemy::TURRET_UP, {3258, 31});

    /*
    ** WALLS
    */

    build_walls(instance, SCROLLING_SPEED, SCROLLING_TICKS);
}

void LevelState::onPause(Game &instance)
{}

void LevelState::onResume(Game &instance)
{}

void LevelState::onTick(Game &instance)
{
    static std::chrono::time_point last_update = std::chrono::system_clock::now();
    std::chrono::milliseconds tick_delay(STAR_SPAWN_DELAY);

    if (std::chrono::system_clock::now() - last_update < tick_delay)
        return;
    last_update = std::chrono::system_clock::now();

    float scale = rand() % 4 + 3;
    float height = rand() % 800;
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

void LevelState::onStop(Game &instance)
{}
