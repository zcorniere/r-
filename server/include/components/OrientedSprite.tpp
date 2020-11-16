#ifndef RTYPE_COMPONENTS_ORIENTED_SPRITE_IMPL_
#define RTYPE_COMPONENTS_ORIENTED_SPRITE_IMPL_

#include "components/OrientedSprite.hpp"

template <std::size_t n>
constexpr std::array<float, n> OrientedSprite::createOrientationTable()
{
    float unit = pi / n;
    std::array<float, n> res;
    for (int i = 0; i < n; i++) {
        res[i] = unit * (2 * i - 1);
        if (res[i] > pi)
            res[i] -= 2 * pi;
    }
    return res;
}

template <std::size_t n>
OrientedSprite::OrientedSprite(std::string sprite,
                               std::array<unsigned, n> tile_ids)
    : tiles(), sprite(sprite)
{
    for (std::size_t i = 0; i < 16; i++) {
        float start = orientationTable<16>[i];
        float end = orientationTable<16>[(i + 1) % 16];
        if (start > end) {
            this->tiles.push_back({start, end + 2 * pi, tile_ids[i]});
            this->tiles.push_back({start - 2 * pi, end, tile_ids[i]});
        } else {
            this->tiles.push_back({start, end, tile_ids[i]});
        }
    }
}
#endif // RTYPE_COMPONENTS_ORIENTED_SPRITE_IMPL_
