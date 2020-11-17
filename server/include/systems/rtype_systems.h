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
#include "components/Lifetime.hpp"
#include "components/OrientedSprite.hpp"
#include "components/PlayerScanner.hpp"
#include "components/RestrictionBox.hpp"
#include "components/EnemyGroup.hpp"
#include "components/Speaker.hpp"
#include "components/PlayerBarracks.hpp"
#include "components/BackgroundMusic.hpp"

// collisions
void collisions_update(Game &instance);
void collision_damages(const CollisionBox &box, Destructible &destructible);
void collision_wormholes(Game &instance);

// movements
void trajectory_applicator(Transform &transform, const Trajectory &trajectory);
void velocity_applicator(Transform &transform, const Velocity &velocity);
void restriction_applicator(Transform &transform, const RestrictionBox &box);

// playership
void playership_ct_input_getter(IInputModule &input, PlayerShipController &controller, const Destructible &destructible);
void playership_animations(PlayerShipController &controller, Sprite &sprite);

// player barracks
void player_barracks_filler(IInputModule &module, PlayerBarracks &barrack);
void player_barracks_ship_summoner(Game &instance);

// Sprite animation
void run_pattern_loops(PatternLoop &loop, Velocity &velocity);
void run_animation_loops(AnimationLoop &loop, Sprite &sprite);
void select_oriented_sprite(Sprite &sprite, const Trajectory &trajectory,
                            const Transform &transform,
                            const OrientedSprite &oriented);

// reaper
void corpse_hider(const Destructible &destructible, Sprite &sprite);
void destructible_reaper(Game &instance);
void lifetime_ager(Lifetime &lifetime);
void lifetime_reaper(Game &instance);

// anim montage
void draw_animmontages(IDisplayModule &display, const Transform &transform, AnimMontage &montage);
void draw_deathmontages(IDisplayModule &display, const Transform &transform, DeathMontage &montage);
void draw_shootmontages(IDisplayModule &display, const Transform &transform, ShootMontage &montage);
void play_deathmontages(Destructible &destructible, DeathMontage &montage);

// wave_cannon
void wave_cannon_input_getter(WaveCannon &cannon, const PlayerShipController &controller);
void wave_cannon_projectile_summoner(Game &instance);
void wave_cannon_montage_player(const WaveCannon &cannon, ShootMontage &montage);

// bydo_shooter
void bydo_shooter_projectile_summoner(Game &instance);
void bydo_charger(BydoShooter &shooter);
void player_scanner_detector(Game &instance);
void bydo_shooter_apply_scanner
(BydoShooter &shooter, const PlayerScanner &scanner, const Transform &transform);

// Enemies
void run_enemy_group(Game &game, EnemyGroup &group, Transform &transform,
                     Destructible &destructible);

// Audio
void speaker_player(IAudioModule &module, Speaker &speaker);
void death_speaker_player(IAudioModule &module, DeathSpeaker &speaker);
void death_speaker_activator(DeathSpeaker &speaker, const Destructible &destructible);
void shoot_speaker_player(IAudioModule &module, ShootSpeaker &speaker);
void shoot_speaker_activator(ShootSpeaker &speaker, const WaveCannon &cannon);
void play_background_music(IAudioModule &audio, BackgroundMusic &music);

#endif
