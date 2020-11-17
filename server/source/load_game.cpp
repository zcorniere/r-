#include "load_game.hpp"
#include "LevelState.hpp"
#include "LobbyState.hpp"
#include "components/PlayerControlled.hpp"
#include "components/WormHole.hpp"
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
    game.componentStorage.registerComponent<PlayerBarracks>();
    game.componentStorage.registerComponent<BackgroundMusic>();
    game.componentStorage.registerComponent<WormHole>();

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
    game.systemStorage.addSystem(collision_wormholes);

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
    game.systemStorage.addSystem(play_background_music);

    // player barracks
    game.systemStorage.addSystem(player_barracks_filler);
    game.systemStorage.addSystem(player_barracks_ship_summoner);
    game.systemStorage.addSystem(player_life_checker);

    /*
    ** STATES
    ** game related logic
    */

    std::unique_ptr<AState> lobby_state(new LobbyState);
    game.stateMachine.setState(std::move(lobby_state));
}

void build_walls(Game &instance, float scrolling_speed)
{
    instance.componentStorage.buildEntity()
        .withComponent(Transform({245 * 4, 194 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(64, 34, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({310 * 4, 211 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(64, 34, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({694 * 4, 211 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(61, 18, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({823 * 4, 195 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(61, 33, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({1334 * 4, 211 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(61, 18, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({1508 * 4, 19 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(58, 78, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({1508 * 4, 147 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(58, 78, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({1478 * 4, 158 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(14, 24, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({1478 * 4, 62 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(14, 24, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({1493 * 4, 56 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(13, 36, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({1493 * 4, 152 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(13, 36, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({1552 * 4, 25 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(36, 17, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({1552 * 4, 65 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(36, 17, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({1552 * 4, 161 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(36, 17, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({1552 * 4, 201 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(36, 17, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({1589 * 4, 0 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(446, 14, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({1782 * 4, 211 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(62, 20, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({1782 * 4, 13 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(62, 20, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({1847 * 4, 12 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(62, 36, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({1847 * 4, 196 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(62, 36, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({2102 * 4, 2 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(638, 13, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({2166 * 4, 17 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(16, 24, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({2340 * 4, 17 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(16, 24, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({2166 * 4, 203 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(16, 24, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({2340 * 4, 203 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(16, 24, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({2318 * 4, 218 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(22, 9, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({2318 * 4, 17 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(22, 9, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({2182 * 4, 17 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(22, 9, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({2182 * 4, 218 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(22, 9, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({2487 * 4, 15 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(61, 17, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({2486 * 4, 196 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(62, 31, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({2743 * 4, 211 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(61, 17, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({2806 * 4, 194 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(62, 35, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({2806 * 4, 2 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(62, 49, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({2868 * 4, 2 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(1163, 15, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({2954 * 4, 168 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(166, 54, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({2954 * 4, 22 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(166, 54, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({2935 * 4, 74 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(157, 17, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({2935 * 4, 153 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(157, 17, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({3252 * 4, 17 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(64, 15, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({3254 * 4, 211 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(62, 18, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({3574 * 4, 18 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(62, 15, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({3638 * 4, 17 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(62, 31, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({3575 * 4, 211 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(61, 20, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
    instance.componentStorage.buildEntity()
        .withComponent(Transform({3638 * 4, 195 * 4}, {0, 0}, {4, 4}))
        .withComponent(CollisionBox(62, 33, 0, 0, 1000))
        .withComponent(GameObject::Wall)
        .withComponent(Velocity(-1 * scrolling_speed, 0))
        .build();
}
