#ifndef RTYPE_SYSTEMS_H
#define RTYPE_SYSTEMS_H

#include "Game.hpp"
#include "components/Sprite.hpp"
#include "components/PlayerShipController.hpp"
#include "components/Enemy.hpp"
#include "components/AnimationLoop.hpp"

void collisions_system(Game &instance);
void playership_ct_input_getter(IInputModule &input, PlayerShipController &controller);
void playership_animations(const PlayerShipController &controller, Sprite &sprite);
void move_enemies(Enemy &enemy, Velocity &velocity);
void run_animation_loops(AnimationLoop &loop, Sprite &sprite);

#endif
