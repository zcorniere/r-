#include "components/Destructible.hpp"
#include "components/Sprite.hpp"
#include "components/Lifetime.hpp"
#include "components/DeathRattle.hpp"
#include "components/AnimationLoop.hpp"
#include "Game.hpp"

void destructible_reaper(Game &instance)
{
    auto destructibles = instance.componentStorage.getComponents<Destructible>();

    for (auto &[id, destructible] : destructibles)
        if (destructible.status == Destructible::Status::Dead)
            instance.componentStorage.destroyEntity(id);
}

void destructible_death_rattle_trigger(Game &instance)
{
    auto death_params = instance.componentStorage.join_components(
        instance.componentStorage.getComponents<Destructible>(),
        instance.componentStorage.getComponents<DeathRattle>()
    );

    for (auto &[id, params] : death_params) {
        auto &[destructible, rattle] = params;
        if (destructible.status == Destructible::Status::Dead)
            rattle.function(instance);
    }
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

void lifetime_death_rattle_trigger(Game &instance)
{
    auto death_params = instance.componentStorage.join_components(
        instance.componentStorage.getComponents<Lifetime>(),
        instance.componentStorage.getComponents<DeathRattle>()
    );

    for (auto &[id, params] : death_params) {
        auto &[lifetime, rattle] = params;
        if (!lifetime.alive)
            rattle.function(instance);
    }
}

void lifetime_ager(Lifetime &lifetime)
{
    if (lifetime.age++ > lifetime.life_expectancy)
        lifetime.alive = false;
}
