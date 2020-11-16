#include "load_game.hpp"
#include "LevelState.hpp"
#include "components/PlayerControlled.hpp"
#include "systems/rtype_systems.h"

#include <time.h>

void load_game(Game &game)
{
    srand(time(NULL));

    /*
    ** COMPONENTS
    ** entity's'datas containers
    */

    game.componentStorage.registerComponent<Transform>();
    game.componentStorage.registerComponent<Sprite>();
    game.componentStorage.registerComponent<PlayerControlled>();
    game.componentStorage.registerComponent<Velocity>();
    game.componentStorage.registerComponent<CollisionBox>();
    game.componentStorage.registerComponent<GameObject>();
    game.componentStorage.registerComponent<PlayerShipController>();
    game.componentStorage.registerComponent<PatternLoop>();
    game.componentStorage.registerComponent<AnimationLoop>();
    game.componentStorage.registerComponent<Destructible>();
    game.componentStorage.registerComponent<AnimMontage>();
    game.componentStorage.registerComponent<DeathMontage>();
    game.componentStorage.registerComponent<WaveCannon>();
    game.componentStorage.registerComponent<Trajectory>();
    game.componentStorage.registerComponent<BydoShooter>();
    game.componentStorage.registerComponent<Lifetime>();
    game.componentStorage.registerComponent<OrientedSprite>();
    game.componentStorage.registerComponent<PlayerScanner>();
    game.componentStorage.registerComponent<ShootMontage>();
    game.componentStorage.registerComponent<RestrictionBox>();
    game.componentStorage.registerComponent<EnemyGroup>();
    game.componentStorage.registerComponent<Speaker>();
    game.componentStorage.registerComponent<DeathSpeaker>();
    game.componentStorage.registerComponent<ShootSpeaker>();

    /*
    ** SYSTEMS
    ** components's logic functions
    */

    // sprite_displayer
    game.systemStorage.addSystem([](IDisplayModule &display,
                                    const Transform &transform,
                                    const Sprite &sprite) {
        if (!sprite.hidden)
            display.drawSprite(sprite.name, transform, sprite.tile_id);
    });

    // reaper
    std::function<void(Game &)> destructible_reaper_system =
        destructible_reaper;
    game.systemStorage.addSystem(destructible_reaper_system);
    game.systemStorage.addSystem(corpse_hider);
    std::function<void(Game &)> lifetime_reaper_system = lifetime_reaper;
    game.systemStorage.addSystem(lifetime_reaper_system);
    game.systemStorage.addSystem(lifetime_ager);

    // playership
    game.systemStorage.addSystem(playership_animations);
    game.systemStorage.addSystem(playership_ct_input_getter);
    game.systemStorage.addSystem(
        [](Velocity &velocity, const PlayerShipController &controller) {
            velocity.x = controller.moovingRight * controller.getSpeed() +
                         controller.moovingLeft * -1 * controller.getSpeed();
            velocity.y = controller.moovingDown * controller.getSpeed() +
                         controller.moovingUp * -1 * controller.getSpeed();
        });

    // collisions
    std::function<void(Game &)> collision_system = collisions_update;
    game.systemStorage.addSystem(collision_system);
    game.systemStorage.addSystem(collision_damages);

    // anim montages
    game.systemStorage.addSystem(play_deathmontages);
    game.systemStorage.addSystem(draw_animmontages);
    game.systemStorage.addSystem(draw_deathmontages);
    game.systemStorage.addSystem(draw_shootmontages);

    game.systemStorage.addSystem(run_animation_loops);
    game.systemStorage.addSystem(run_pattern_loops);
    game.systemStorage.addSystem(select_oriented_sprite);

    // wave cannon
    std::function<void(Game &)> wave_cannon_projectile_system =
        wave_cannon_projectile_summoner;
    game.systemStorage.addSystem(wave_cannon_montage_player);
    game.systemStorage.addSystem(wave_cannon_projectile_system);
    game.systemStorage.addSystem(wave_cannon_input_getter);

    // movement
    game.systemStorage.addSystem(velocity_applicator);
    game.systemStorage.addSystem(trajectory_applicator);
    game.systemStorage.addSystem(restriction_applicator);

    // bydo shooter
    std::function<void(Game &)> bydo_shooter_projectile_system =
        bydo_shooter_projectile_summoner;
    game.systemStorage.addSystem(bydo_shooter_projectile_system);
    game.systemStorage.addSystem(bydo_charger);
    std::function<void(Game &)> player_scanner_detector_system =
        player_scanner_detector;
    game.systemStorage.addSystem(player_scanner_detector_system);
    game.systemStorage.addSystem(bydo_shooter_apply_scanner);

    game.systemStorage.addSystem(run_enemy_group);

    // audio
    game.systemStorage.addSystem(speaker_player);
    game.systemStorage.addSystem(death_speaker_player);
    game.systemStorage.addSystem(death_speaker_activator);
    game.systemStorage.addSystem(shoot_speaker_player);
    game.systemStorage.addSystem(shoot_speaker_activator);

    /*
    ** STATES
    ** game related logic
    */

    std::unique_ptr<AState> level_state(new LevelState);
    game.stateMachine.setState(std::move(level_state));
}
