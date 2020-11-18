#ifndef RTYPE_COMPONENTS_ORIENTED_SPRITE_H_
#define RTYPE_COMPONENTS_ORIENTED_SPRITE_H_

#include <array>
#include <vector>
#include <string>

struct OrientedSprite {
    // tile ids given in trigonometric order :
    // right
    // down
    // left
    // up
    template <std::size_t n>
    OrientedSprite(std::string sprite, std::array<unsigned, n>);

    struct OrientedTile {
        float angle_start;
        float angle_end;
        unsigned tile_id;
    };

    std::string sprite;
    std::vector<OrientedTile> tiles;

    const OrientedTile &getNearestTile(float x, float y) const;
    const OrientedTile &getNearestTile(float angle) const;

    static constexpr float pi = 3.14159265358979323846;

    template <std::size_t n>
    static constexpr std::array<float, n> createOrientationTable();

    template <std::size_t n>
    static constexpr std::array<float, n> orientationTable =
        createOrientationTable<n>();
};

#include "components/OrientedSprite.tpp"

#endif // RTYPE_COMPONENTS_ORIENTED_SPRITE_H_
