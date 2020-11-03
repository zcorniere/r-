#ifndef BABEL_SYSTEM_IMPL_
#define BABEL_SYSTEM_IMPL_

#include <functional>
#include <tuple>

#include "System.hpp"

template <typename T>
struct wrapper : public wrapper<decltype(&T::operator())> {
};

template <typename Fn, typename ReturnType, typename... Components>
struct wrapper<ReturnType (Fn::*)(Components...) const> {
    static std::function<void(ComponentStorage &)> wrap_system(Fn system)
    {
        return [system](ComponentStorage &storage) {
            auto components_map =
                join_components(storage.getComponents<Components>()...);

            for (auto &[_, components] : components_map)
                std::apply(system, components);
        };
    }
};

System::System(SystemFunction auto system)
    : m_call_wrapper(wrapper<decltype(system)>::wrap_system(system))
{
}

void System::call(ComponentStorage &storage) const
{
    m_call_wrapper(storage);
}

#endif // BABEL_SYSTEM_IMPL_
