#include "components/OrientedSprite.hpp"
#include <iostream>

int main(void)
{
    OrientedSprite sprite("a_sprite",
                          std::array<unsigned, 16>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
                                                   10, 11, 12, 13, 14, 15});

    for (auto tile : sprite.tiles) {
        std::clog << "start: " << tile.angle_start << " end: " << tile.angle_end
                  << " id: " << tile.tile_id << std::endl;
    }
    std::clog << "right: " << sprite.getNearestTile(0.0).tile_id << std::endl;
    std::clog << "right-down: "
              << sprite.getNearestTile(OrientedSprite::pi / 4.0).tile_id
              << std::endl;
    std::clog << "down"
              << sprite.getNearestTile(OrientedSprite::pi / 2.0).tile_id
              << std::endl;
    std::clog << "left: " << sprite.getNearestTile(OrientedSprite::pi).tile_id
              << std::endl;
    std::clog << "up: "
              << sprite.getNearestTile(3.0 * OrientedSprite::pi / 2.0).tile_id
              << std::endl;
    return 0;
}
