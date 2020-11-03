#ifndef BABEL_SYSTEM_H_
#define BABEL_SYSTEM_H_

#include "ComponentStorage.hpp"
#include <functional>

template <typename... Components>
class System
{
  public:
    System(std::function<void(Components...)>);

    void call(ComponentStorage &) const;

  private:
    std::function<void(Components...)> m_system;
};

#include "System.tpp"

#endif // BABEL_SYSTEM_H_
