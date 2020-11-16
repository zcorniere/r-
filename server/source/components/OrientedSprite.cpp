#include "components/OrientedSprite.hpp"
#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <optional>

const OrientedSprite::OrientedTile &OrientedSprite::getNearestTile(
    float x, float y) const
{
    return getNearestTile(atan2(y, x));
}

const OrientedSprite::OrientedTile &OrientedSprite::getNearestTile(
    float angle) const
{

    if (angle >= pi)
        angle -= 2 * pi;
    auto res =
        std::ranges::find_if(this->tiles, [angle](const OrientedTile &tile) {
            return angle >= tile.angle_start && angle < tile.angle_end;
        });
    if (res == this->tiles.end())
        return this->tiles[0];
    else
        return *res;
}
