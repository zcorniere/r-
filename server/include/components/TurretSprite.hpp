#ifndef RTYPE_TURRETSPRITE_H_
#define RTYPE_TURRETSPRITE_H_

#include "components/OrientedSprite.hpp"

struct TurretSprite
{
    enum TurretSide
    {
        UP,
        DOWN
    } side;
};

#endif // RTYPE_TURRETSPRITE_H_
