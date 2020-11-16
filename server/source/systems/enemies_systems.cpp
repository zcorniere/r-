#include "components/EnemyGroup.hpp"
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
