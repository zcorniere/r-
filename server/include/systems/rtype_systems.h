#ifndef RTYPE_SYSTEMS_H
#define RTYPE_SYSTEMS_H

#include "Game.hpp"
#include "components/Sprite.hpp"
#include "components/PlayerShipController.hpp"
#include "components/PatternLoop.hpp"
#include "components/AnimationLoop.hpp"
#include "components/CollisionBox.hpp"
#include "components/Destructible.hpp"
#include "components/AnimMontage.hpp"
#include "components/WaveCannon.hpp"
#include "components/Trajectory.hpp"
#include "components/BydoShooter.hpp"

// collisions
void collisions_update(Game &instance);
void collision_damages(const CollisionBox &box, Destructible &destructible);

// movements
void trajectory_applicator(Transform &transform, const Trajectory &trajectory);
void velocity_applicator(Transform &transform, const Velocity &velocity);

// playership
void playership_ct_input_getter(IInputModule &input, PlayerShipController &controller, const Destructible &destructible);
void playership_animations(const PlayerShipController &controller, Sprite &sprite);

void run_pattern_loops(PatternLoop &loop, Velocity &velocity);
void run_animation_loops(AnimationLoop &loop, Sprite &sprite);

// reaper
void corpse_hider(const Destructible &destructible, Sprite &sprite);
void destructible_reaper(Game &instance);

// anim montage
void draw_animmontages(IDisplayModule &display, const Transform &transform, AnimMontage &montage);
void draw_deathmontages(IDisplayModule &display, const Transform &transform, DeathMontage &montage);
void play_deathmontages(Destructible &destructible, DeathMontage &montage);

// wave_cannon
void wave_cannon_input_getter(WaveCannon &cannon, const PlayerShipController &controller);
void wave_cannon_projectile_summoner(Game &instance);

// bydo_shooter
void bydo_shooter_projectile_summoner(Game &instance);
void bydo_charger(BydoShooter &shooter);

#endif
