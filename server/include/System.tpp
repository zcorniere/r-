#ifndef BABEL_SYSTEM_IMPL_
#define BABEL_SYSTEM_IMPL_

#include <functional>
#include <tuple>

#include "System.hpp"

template <typename... Components>
System<Components...>::System(
    std::function<void(Components...)> system)
    : m_system(system)
{
}

template <typename... Components>
void System<Components...>::call(ComponentStorage &storage) const
{
    auto components_map =
        join_components(storage.getComponents<Components>()...);

    for (auto &[_, components] : components_map)
        std::apply(m_system, components);
}

#endif // BABEL_SYSTEM_IMPL_
