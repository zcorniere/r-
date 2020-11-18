#include "components/Transform.hpp"
#include "components/Velocity.hpp"
#include "components/Trajectory.hpp"
#include "components/RestrictionBox.hpp"
#include "components/Paralyzed.hpp"
#include <iostream>

void velocity_applicator(Transform &transform, const Velocity &velocity)
{
        transform.location.x += velocity.x;
        transform.location.y += velocity.y;
}

void trajectory_applicator(Transform &transform, const Trajectory &trajectory)
{
    trajectory.update(transform);
}

void restriction_applicator(Transform &transform, const RestrictionBox &box)
{
    transform.location.x = (transform.location.x < box.x)? box.x : transform.location.x;
    transform.location.y = (transform.location.y < box.y)? box.y : transform.location.y;
    transform.location.x = (transform.location.x > box.width)? box.width : transform.location.x;
    transform.location.y = (transform.location.y > box.height)? box.height : transform.location.y;
}

void paralyzer(Paralyzed &paralyzed, Velocity &velocity)
{
    if (paralyzed.ticks > 0) {
        velocity = {0, 0};
        paralyzed.ticks--;
    }
}
