#ifndef COLLISION_BOX_HPP
#define COLLISION_BOX_HPP

#include "GameObject.hpp"
#include <functional>

struct CollisionBox {
    float width;
    float height;
    std::function<void()> onCollision = [](){};
    float offset_x = 0;
    float offset_y = 0;
};

#endif
