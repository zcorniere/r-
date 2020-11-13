#ifndef RTYPE_ENEMIES_H_
#define RTYPE_ENEMIES_H_

#include "ComponentStorage.hpp"
#include "components/AnimMontage.hpp"
#include "components/AnimationLoop.hpp"
#include "components/CollisionBox.hpp"
#include "components/PatternLoop.hpp"
#include "components/Sprite.hpp"
#include "components/Trajectory.hpp"
#include <variant>

struct Enemy {
    CollisionBox collision;
    std::variant<Trajectory, PatternLoop> movement;
    std::variant<Sprite, AnimationLoop> animation;
    int health;
    DeathMontage death_montage;

    static const Enemy BUG;
    static const Enemy PATA_PATA;

    ComponentStorage::EntityBuilder build(
        ComponentStorage::EntityBuilder builder) const;
};

#endif // RTYPE_ENEMIES_H_
