#ifndef BYDO_SHOOTER_HPP
#define BYDO_SHOOTER_HPP

#include "components/Transform.hpp"

struct BydoShooter {
    enum class Status {
        Disabled,
        Charging,
        Firing,
    };
    unsigned fire_delay = 1000;
    float fire_probability = 0.5;
    Dimensional aim_direction = {-1, 0};
    float precision = 0.9;
    float projectile_speed = 3;
    Status status = Status::Charging;
    unsigned charging_ticks = 0;
};

#endif
