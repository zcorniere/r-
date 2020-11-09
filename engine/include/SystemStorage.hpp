#ifndef RTYPE_SYSTEM_STORAGE_
#define RTYPE_SYSTEM_STORAGE_

#include "System.hpp"

class SystemStorage
{
  public:
    SystemStorage();

    void addSystem(System system);

    void runTick(Game &) const;

  private:
    std::vector<System> m_systems;
};

#endif // RTYPE_SYSTEM_STORAGE_
