#include "components/PatternLoop.hpp"
#include "systems/rtype_systems.h"

void run_pattern_loops(PatternLoop &loop, Velocity &velocity)
{
    if (loop.pattern.size() == 0)
        return;
    loop.duration_elapsed++;
    if (loop.duration_elapsed >= loop.currentPattern().duration) {
        loop.duration_elapsed = 0;
        loop.pattern_id = (loop.pattern_id + 1) % loop.pattern.size();
    }
    velocity = loop.currentPattern().velocity;
}
