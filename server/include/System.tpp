#ifndef BABEL_SYSTEM_IMPL_
#define BABEL_SYSTEM_IMPL_

#include <concepts>
#include <functional>
#include <tuple>

#include "System.hpp"

template <typename... Components>
System::System(std::function<void(Components...)> system)
    : m_call_wrapper([system](ComponentStorage &storage) {
          auto components_map =
              join_components(storage.getComponents<Components>()...);

          for (auto &[_, components] : components_map)
              std::apply(system, components);
      })
{
}

void System::call(ComponentStorage &storage) const
{
    m_call_wrapper(storage);
}

#endif // BABEL_SYSTEM_IMPL_
