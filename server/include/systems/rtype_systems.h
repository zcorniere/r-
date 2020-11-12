#ifndef RTYPE_SYSTEMS_H
#define RTYPE_SYSTEMS_H

#include "Game.hpp"
#include "components/Sprite.hpp"
#include "components/PlayerShipController.hpp"
#include "components/Enemy.hpp"
#include "components/AnimationLoop.hpp"
#include "components/CollisionBox.hpp"
#include "components/Destructible.hpp"
#include "components/AnimMontage.hpp"

void collisions_update(Game &instance);
void playership_ct_input_getter(IInputModule &input, PlayerShipController &controller);
void playership_animations(const PlayerShipController &controller, Sprite &sprite);
void move_enemies(Enemy &enemy, Velocity &velocity);
void run_animation_loops(AnimationLoop &loop, Sprite &sprite);
void destructible_reaper(Game &instance);
void collision_damages(const CollisionBox &box, Destructible &destructible);
void draw_animmontages(IDisplayModule &display, const Transform &transform, AnimMontage &montage);
void play_death_montages(Destructible &destructible, AnimMontage &montage);

#endif
