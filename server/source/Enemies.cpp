#include "Enemies.hpp"
#include "components/Destructible.hpp"
#include <cmath>

const Enemy Enemy::BUG = {
    CollisionBox{21, 20, 4, 2, 1}, Trajectory{[](Transform &t) {
        t.location.x -= 1;
        t.location.y = std::cos(t.location.x * 0.01) * 200 + 300;
    }},
    Sprite{"bug", 4}, 1, DeathMontage("explosions", {0, 1, 2, 3, 4, 5}, 7)};

const Enemy Enemy::PATA_PATA = {
    CollisionBox{21, 20, 4, 2, 1},
    PatternLoop{{Pattern{{-1, 1}, 60}, Pattern{{-1, -1}, 60}}},
    AnimationLoop{{{"enemy_flap", 0},
                   {"enemy_flap", 1},
                   {"enemy_flap", 2},
                   {"enemy_flap", 3},
                   {"enemy_flap", 4},
                   {"enemy_flap", 5},
                   {"enemy_flap", 6},
                   {"enemy_flap", 7}},
                  15},
    1, DeathMontage("explosions", {0, 1, 2, 3, 4, 5}, 7)};

ComponentStorage::EntityBuilder Enemy::build(
    ComponentStorage::EntityBuilder builder) const
{
    if (auto animation = std::get_if<AnimationLoop>(&this->animation)) {
        builder.withComponent(animation->frames[0]);
    }
    if (std::holds_alternative<PatternLoop>(this->movement)) {
        builder.withComponent(Velocity{0, 0});
    }
    return builder.withComponent(this->collision)
        .withComponent(this->movement)
        .withComponent(this->animation)
        .withComponent(Destructible{this->health, true})
        .withComponent(this->death_montage)
        .withComponent(GameObject::Enemy);
}
