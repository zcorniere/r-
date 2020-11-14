#include "components/BydoShooter.hpp"
#include "components/Sprite.hpp"
#include "components/CollisionBox.hpp"
#include "components/Velocity.hpp"
#include "components/Destructible.hpp"
#include "components/GameObject.hpp"
#include "components/Lifetime.hpp"
#include "components/PlayerScanner.hpp"
#include "components/PlayerShipController.hpp"
#include "Game.hpp"
#include <cstdlib>
#include <iostream>

// Bydo Shooter Projectile params
constexpr char BSP_SPRITESHEET[] = "effects";
constexpr unsigned BSP_ID = 90;
constexpr float BSP_OFFSET_X = 5;
constexpr float BSP_OFFSET_Y = 10;
constexpr unsigned BSP_ROUGHNESS = 1;

void bydo_charger(BydoShooter &shooter)
{
    if (shooter.status != BydoShooter::Status::Charging)
        return;
    if (shooter.charging_ticks >= shooter.fire_delay) {
        shooter.status = BydoShooter::Status::Firing;
        shooter.charging_ticks = 0;
    }
    shooter.charging_ticks++;
}

void bydo_shooter_projectile_summoner(Game &instance)
{
    auto shooter_params = instance.componentStorage.join_components(
        instance.componentStorage.getComponents<BydoShooter>(),
        instance.componentStorage.getComponents<Transform>()
    );

    for (auto &[id, param] : shooter_params) {
        auto &[shooter, transform] = param;
        if (shooter.status == BydoShooter::Status::Firing) {
            if (rand() % 100 > shooter.fire_probability * 100)
                continue;
            instance.componentStorage.buildEntity()
                .withComponent(Sprite(BSP_SPRITESHEET, BSP_ID))
                .withComponent(Transform(
                    Dimensional(
                        transform.location.x + BSP_OFFSET_X * transform.scale.x,
                        transform.location.y + BSP_OFFSET_Y * transform.scale.y
                    ),
                    Dimensional(0, 0),
                    Dimensional(0.25, 0.25)
                ))
                .withComponent(CollisionBox(4, 4, 0, 0, 1, {GameObject::EnemyProjectile, GameObject::Enemy}))
                .withComponent(Destructible(1))
                .withComponent(Velocity({
                    shooter.aim_direction.x * shooter.projectile_speed,
                    (shooter.aim_direction.y + (1 - shooter.precision) * (rand() % 2 - 1))
                    * shooter.projectile_speed
                }))
                .withComponent(GameObject::EnemyProjectile)
                .withComponent(Lifetime(1000))
                .build();
            shooter.status = BydoShooter::Status::Charging;
        }
    }
}

void player_scanner_detector(Game &instance)
{
    auto players_params = instance.componentStorage.join_components(
        instance.componentStorage.getComponents<PlayerShipController>(),
        instance.componentStorage.getComponents<Transform>()
    );

    PlayerScanner::m_playerLocations.clear();

    for (auto &[id, param] : players_params) {
        auto &[controller, transform] = param;
        PlayerScanner::m_playerLocations.push_back(transform.location);
    }
}

void bydo_shooter_apply_scanner
(BydoShooter &shooter, const PlayerScanner &scanner, const Transform &transform)
{
    float distance = scanner.distanceToClosestPlayer(transform.location);

    std::cout << "Player distance: " << distance << std::endl;
    if (distance == -1 || distance > scanner.range) {
        shooter.status = BydoShooter::Status::Disabled;
        return;
    }
    if (shooter.status == BydoShooter::Status::Disabled)
        shooter.status = BydoShooter::Status::Charging;
    shooter.aim_direction = scanner.computeAimTrajectory(transform.location);
}
