#include "components/BydoShooter.hpp"
#include "components/Sprite.hpp"
#include "components/CollisionBox.hpp"
#include "components/Velocity.hpp"
#include "components/Destructible.hpp"
#include "components/GameObject.hpp"
#include "components/Lifetime.hpp"
#include "Game.hpp"
#include <cstdlib>

// Bydo Shooter Projectile params
constexpr char BSP_SPRITESHEET[] = "effects";
constexpr unsigned BSP_ID = 90;
constexpr float BSP_OFFSET_X = -20;
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
            if (rand() % 100 < shooter.fire_probability * 100)
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
                .withComponent(CollisionBox(4, 4))
                .withComponent(Destructible(1))
                .withComponent(Velocity({
                    shooter.aim_direction.x * shooter.projectile_speed,
                    (shooter.aim_direction.y + (1 - shooter.precision) * (rand() % 2 - 1))
                    * shooter.projectile_speed
                }))
                .withComponent(GameObject::EnemyProjectile)
                .withComponent(Lifetime(500))
                .build();
            shooter.status = BydoShooter::Status::Charging;
        }
    }
}
