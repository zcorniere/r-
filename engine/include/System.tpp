#ifndef BABEL_SYSTEM_IMPL_
#define BABEL_SYSTEM_IMPL_

#include <functional>
#include <tuple>

#include "System.hpp"
#include "function_traits.hpp"
template <typename T>
using cleaned_component =
    typename std::remove_cv<typename std::remove_reference<T>::type>::type;

template <typename T>
struct wrapper : public wrapper<typename function_traits<T>::args_type> {
};

template <typename... Components>
struct wrapper<std::tuple<Components...>> {
    static constexpr auto wrap_system(auto system)
    {
        return [system](ComponentStorage &storage) {
            auto components_map = storage.join_components(
                storage.getComponents<cleaned_component<Components>>()...);

            for (auto &[_, components] : components_map)
                std::apply(system, components);
        };
    }
};

System::System(SystemFunction auto system)
    : m_call_wrapper(wrapper<decltype(system)>::wrap_system(system))
{
}

#endif // BABEL_SYSTEM_IMPL_
