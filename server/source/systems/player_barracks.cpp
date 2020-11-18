#include "Modules.hpp"
#include "Game.hpp"
#include "components/PlayerBarracks.hpp"
#include "components/Sprite.hpp"
#include "components/PlayerShipController.hpp"
#include "components/Velocity.hpp"
#include "components/CollisionBox.hpp"
#include "components/GameObject.hpp"
#include "components/PatternLoop.hpp"
#include "components/AnimationLoop.hpp"
#include "components/Destructible.hpp"
#include "components/AnimMontage.hpp"
#include "components/WaveCannon.hpp"
#include "components/Trajectory.hpp"
#include "components/BydoShooter.hpp"
#include "components/PlayerScanner.hpp"
#include "components/RestrictionBox.hpp"
#include "components/EnemyGroup.hpp"
#include "components/Speaker.hpp"
#include "components/Destructible.hpp"
#include "components/PlayerShipController.hpp"
#include "components/Paralyzed.hpp"
#include "components/Invulnerable.hpp"
#include "components/Lifetime.hpp"

#include <iostream>
#include <cstdlib>
#include <string>

void player_barracks_filler(IInputModule &module, PlayerBarracks &barrack)
{
    if (!barrack.connectionsOpen || !barrack.active)
        return;
    for (short i = 0; i <= 3; i++) {
        if (!barrack.playerConnected[i] && module.isKeyPressed(i, Input::Z)) {
            barrack.playerConnected[i] = true;
            std::cout << "Player " << i << " joined !\n";
        }
    }
}

void player_barracks_ship_summoner(Game &instance)
{
    auto &barracks = instance.componentStorage.getComponents<PlayerBarracks>();
    unsigned god_duration = 700;

    std::string god_mode((getenv("RTYPE_GOD_MODE"))? getenv("RTYPE_GOD_MODE") : "false");
    if (god_mode == "true")
        god_duration = 4294967295;

    for (auto &[id, barrack] : barracks) {
        if (!barrack.active)
            continue;
        for (short i = 0; i <= 3; i++) {
            if (barrack.playerConnected[i] && !barrack.playerSpawned[i] ||
        !barrack.playerAlive[i] && barrack.autoRespawn && barrack.playerConnected[i]) {
                instance.componentStorage.buildEntity()
                    .withComponent(Sprite("player_ships", 2 + 10 * i))
                    .withComponent(Transform(Dimensional(-100, 225 + 135 * i), Dimensional(0.1, 0),
                    Dimensional(3, 3)))
                    .withComponent(PlayerShipController(i, 2.5))
                    .withComponent(Velocity(0, 0))
                    .withComponent(GameObject::PlayerShip)
                    .withComponent(CollisionBox(30, 10, 0, 3, 10))
                    .withComponent(Destructible(1, true))
                    .withComponent(DeathMontage("effects", {80, 81, 82, 83, 84}, 7))
                    .withComponent(ShootMontage("effects", {20, 21}, 7))
                    .withComponent(RestrictionBox(-100, 0, 2000, 1000))
                    .withComponent(WaveCannon())
                    .withComponent(DeathSpeaker("playership-explosion"))
                    .withComponent(ShootSpeaker("laser-burst", 0.1, 0.1))
                    .withComponent(Paralyzed(500))
                    .withComponent(Trajectory([](Transform &t){
                        if (t.rotation.x != 0) {
                            t.location.x++;
                            if (t.location.x > 400)
                                t.rotation.x = 0;
                        }
                    }))
                    .withComponent(Invulnerable(god_duration))
                    .build();
                barrack.playerSpawned[i] = true;
                barrack.playerAlive[i] = true;
                instance.componentStorage.buildEntity()
                    .withComponent(Sprite("player_ships", 1))
                    .withComponent(AnimationLoop({
                    {"effects", 0},
                    {"effects", 1},
                    {"effects", 2},
                    {"effects", 3}
                    }, 10))
                    .withComponent(Transform(Dimensional(-165, (225 + 135 * i) - 10), {0, 0}, {2, 2}))
                    .withComponent(Velocity({1, 0}))
                    .withComponent(Lifetime(500))
                    .build();
                }
        }
    }
}

void player_life_checker(Game &instance)
{
    auto players_params = instance.componentStorage.join_components(
        instance.componentStorage.getComponents<Destructible>(),
        instance.componentStorage.getComponents<PlayerShipController>()
    );
    auto &barracks = instance.componentStorage.getComponents<PlayerBarracks>();

    for (auto &[id, barrack] : barracks) {
        for (auto &[id, params] : players_params) {
            auto &[destructible, controller] = params;
            barrack.playerAlive[controller.getPlayerId()] =
            destructible.status == Destructible::Status::Alive;
        }
    }
}
