#include "components/EnemyGroup.hpp"
#include "components/TurretSprite.hpp"
#include "systems/rtype_systems.h"

void run_enemy_group(Game &game, EnemyGroup &group, Transform &transform,
                     Destructible &destructible)
{
    if (group.enemies_spawned < group.number) {
        group.time_elapsed++;
        if (group.time_elapsed >= group.delay) {
            group.time_elapsed = 0;
            group.enemies_spawned++;
            game.componentStorage.buildEntity()
                .withBuilder(group.enemy)
                .withComponent(transform)
                .build();
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
