#include "components/OrientedSprite.hpp"
#include "systems/rtype_systems.h"

void select_oriented_sprite(Sprite &sprite, const Trajectory &trajectory,
                            const Transform &transform,
                            const OrientedSprite &oriented)
{
    Transform new_transform = transform;
    trajectory.update(new_transform);
    float dx = new_transform.location.x - transform.location.x;
    float dy = new_transform.location.y - transform.location.y;
    sprite.tile_id = oriented.getNearestTile(dx, dy).tile_id;
}
