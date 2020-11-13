#include "Enemies.hpp"
#include "components/Destructible.hpp"
#include <cmath>

const Enemy Enemy::BUG = {
    CollisionBox{21, 20, 4, 2, 1}, Trajectory{[](Transform &t) {
        t.location.x -= 1;
        t.location.y = std::cos(t.location.x * 0.01) * 200 + 300;
    }},
    Sprite{"bug", 4}, 1, DeathMontage("explosions", {0, 1, 2, 3, 4, 5}, 7)};

ComponentStorage::EntityBuilder &Enemy::build(
    ComponentStorage::EntityBuilder &builder) const
{
    return builder.withComponent(this->collision)
        .withComponent(this->movement)
        .withComponent(this->animation)
        .withComponent(Destructible{this->health, true})
        .withComponent(this->death_montage)
        .withComponent(GameObject::Enemy);
}
