#include "components/PlayerScanner.hpp"
#include <cmath>

std::vector<std::reference_wrapper<Dimensional>> PlayerScanner::m_playerLocations = {};

PlayerScanner::PlayerScanner(float _range)
: range(_range)
{}

static float computeDistance(Dimensional a, Dimensional b)
{
    float x = b.x - a.x;
    float y = b.y - a.y;

    return std::sqrt(y * y + x * x);
}

Dimensional PlayerScanner::getClosestPlayerLocation(Dimensional location) const
{
    if (m_playerLocations.empty())
        return {0, 0};
    Dimensional closest = m_playerLocations.at(0);
    for (auto &plocation : m_playerLocations) {
        if (computeDistance(location, plocation) < computeDistance(location, closest))
            closest = plocation;
    }
    return closest;
}

float PlayerScanner::distanceToClosestPlayer(Dimensional location) const
{
    if (m_playerLocations.empty())
        return -1;
    return computeDistance(getClosestPlayerLocation(location), location);
}

Dimensional PlayerScanner::computeAimTrajectory(Dimensional location) const
{
    if (m_playerLocations.empty())
        return {-1, 0};
    Dimensional objective = getClosestPlayerLocation(location);
    Dimensional trajectory = {objective.x - location.x, objective.y - location.y};
    if (abs(trajectory.x) > abs(trajectory.y))
        return {trajectory.x / abs(trajectory.x), trajectory.y / abs(trajectory.x)};
    return {trajectory.x / abs(trajectory.y), trajectory.y / abs(trajectory.y)};
}
