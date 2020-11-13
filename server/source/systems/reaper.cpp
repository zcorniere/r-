#include "components/Destructible.hpp"
#include "components/Sprite.hpp"
#include "components/Lifetime.hpp"
#include "Game.hpp"

void destructible_reaper(Game &instance)
{
    auto destructibles = instance.componentStorage.getComponents<Destructible>();

    for (auto &[id, destructible] : destructibles)
        if (destructible.status == Destructible::Status::Dead)
            instance.componentStorage.destroyEntity(id);
}

void corpse_hider(const Destructible &destructible, Sprite &sprite)
{
    if (destructible.status != Destructible::Status::Alive)
        sprite.hidden = true;
}

void lifetime_reaper(Game &instance)
{
    auto lifetimes = instance.componentStorage.getComponents<Lifetime>();

    for (auto &[id, lifetime] : lifetimes)
        if (!lifetime.alive)
            instance.componentStorage.destroyEntity(id);
}

void lifetime_ager(Lifetime &lifetime)
{
    if (lifetime.age++ > lifetime.life_expectancy)
        lifetime.alive = false;
}
