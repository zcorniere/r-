#ifndef PLAYER_SCANNER_HPP
#define PLAYER_SCANNER_HPP

#include "components/Transform.hpp"
#include <vector>
#include <functional>

class PlayerScanner {
public:
    float range;
    static std::vector<std::reference_wrapper<Dimensional>> m_playerLocations;

    PlayerScanner(float _range);
    Dimensional getClosestPlayerLocation(Dimensional location) const;
    float distanceToClosestPlayer(Dimensional location) const;
    Dimensional computeAimTrajectory(Dimensional location) const;
};

#endif
