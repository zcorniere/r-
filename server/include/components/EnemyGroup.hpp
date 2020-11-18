#ifndef __ENEMYGROUP_H_
#define __ENEMYGROUP_H_

#include "Enemies.hpp"

struct EnemyGroup {
    const Enemy &enemy;
    unsigned number;
    unsigned delay;
    unsigned random_interval = 0;

    unsigned enemies_spawned = 0;
    unsigned time_remaning = 0;
};

#endif // __ENEMYGROUP_H_
