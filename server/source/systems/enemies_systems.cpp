#include "components/EnemyGroup.hpp"
#include "components/TurretSprite.hpp"
#include "systems/rtype_systems.h"

void run_enemy_group(Game &game, EnemyGroup &group, Transform &transform,
                     Destructible &destructible)
{
    if (group.enemies_spawned < group.number) {
        if (group.time_remaning == 0) {
            if (group.random_interval == 0)
                group.time_remaning = group.delay;
            else
                group.time_remaning = group.delay + std::rand() % group.random_interval;
            group.enemies_spawned++;
            game.componentStorage.buildEntity()
                .withBuilder(group.enemy)
                .withComponent(transform)
                .build();
        } else {
            group.time_remaning--;
        }
    } else {
        destructible.status = Destructible::Status::Dead;
    }
}

void rotate_turret(TurretSprite &turret, const OrientedSprite &orientation,
                   const PlayerScanner &scanner, const Transform &transform,
                   Sprite &sprite)
{
    auto shooting_direction = scanner.computeAimTrajectory(transform.location);
    auto tile = orientation.getNearestTile(shooting_direction.x, shooting_direction.y);
    if (turret.side == TurretSprite::UP && shooting_direction.y < 0)
        return;
    if (turret.side == TurretSprite::DOWN && shooting_direction.y > 0)
        return;
    sprite.tile_id = tile.tile_id;
}
