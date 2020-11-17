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
#include <iostream>

void player_barracks_filler(IInputModule &module, PlayerBarracks &barrack)
{
    if (!barrack.connectionsOpen)
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

    for (auto &[id, barrack] : barracks) {
        for (short i = 0; i <= 3; i++) {
            if (barrack.playerConnected[i] && !barrack.playerSpawned[i]) {
                instance.componentStorage.buildEntity()
                    .withComponent(Sprite("player_ships", 2 + 10 * i))
                    .withComponent(Transform(Dimensional(10, 225 + 135 * i), Dimensional(0, 0),
                    Dimensional(3, 3)))
                    .withComponent(PlayerShipController(i, 2.5))
                    .withComponent(Velocity(0, 0))
                    .withComponent(GameObject::PlayerShip)
                    .withComponent(CollisionBox(30, 10, 0, 3, 10))
                    .withComponent(Destructible(1, true))
                    .withComponent(DeathMontage("effects", {80, 81, 82, 83, 84}, 7))
                    .withComponent(ShootMontage("effects", {20, 21}, 7))
                    .withComponent(RestrictionBox(0, 0, 2000, 1000))
                    .withComponent(WaveCannon())
                    .withComponent(DeathSpeaker("../draft/assets/playership-explosion.ogg"))
                    .withComponent(ShootSpeaker("../draft/assets/laser-burst.ogg", 0.1, 0.1))
                    .build();
                barrack.playerSpawned[i] = true;
                barrack.playerAlive[i] = true;
            }
        }
    }
}
