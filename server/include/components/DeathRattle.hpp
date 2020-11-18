#ifndef DEATH_RATTLE_HPP
#define DEATH_RATTLE_HPP

#include "Game.hpp"
#include <functional>

struct DeathRattle {
    std::function<void(Game &)> function;
};

#endif
