#ifndef __ENEMYGROUP_H_
#define __ENEMYGROUP_H_

#include "Enemies.hpp"

struct EnemyGroup {
    const Enemy &enemy;
    unsigned number;
    unsigned delay;

    unsigned enemies_spawned = 0;
    unsigned time_elapsed = 0;
};

#endif // __ENEMYGROUP_H_
