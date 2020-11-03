#ifndef BABEL_SYSTEM_H_
#define BABEL_SYSTEM_H_

#include "ComponentStorage.hpp"
#include <functional>

class System
{
  public:
        template <typename F>
        System(F system);

    void call(ComponentStorage &) const;

  private:
    std::function<void(ComponentStorage &)> m_call_wrapper;
};

#include "System.tpp"

#endif // BABEL_SYSTEM_H_
