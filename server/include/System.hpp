#ifndef BABEL_SYSTEM_H_
#define BABEL_SYSTEM_H_

#include "ComponentStorage.hpp"
#include <functional>
#include <concepts>

class System
{
  public:
    template <typename... Components>
    System(std::function<void(Components...)> system);

    void call(ComponentStorage &) const;

  private:
    std::function<void(ComponentStorage &)> m_call_wrapper;
};

#include "System.tpp"

#endif // BABEL_SYSTEM_H_
