#include "components/Destructible.hpp"
#include "Game.hpp"

void destructible_reaper(Game &instance)
{
    auto destructibles = instance.componentStorage.getComponents<Destructible>();

    for (auto &[id, destructible] : destructibles)
        if (destructible.status == Destructible::Status::Dead)
            instance.componentStorage.destroyEntity(id);
}
