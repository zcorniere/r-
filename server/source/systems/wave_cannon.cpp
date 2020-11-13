#include "components/WaveCannon.hpp"
#include "components/PlayerShipController.hpp"
#include "components/Transform.hpp"
#include "components/Sprite.hpp"
#include "components/Velocity.hpp"
#include "Game.hpp"

void wave_cannon_input_getter(WaveCannon &cannon, const PlayerShipController &controller)
{
    if (cannon.status == WaveCannon::Status::Inactive && controller.firing)
        cannon.status = WaveCannon::Status::Charging;
    else if (cannon.status == WaveCannon::Status::Charging && !controller.firing)
        cannon.status = WaveCannon::Status::Firing;
}

void wave_cannon_projectile_summoner(Game &instance)
{
    auto cannon_params = instance.componentStorage.join_components(
        instance.componentStorage.getComponents<WaveCannon>(),
        instance.componentStorage.getComponents<Transform>()
    );

    for (auto &[id, param] : cannon_params) {
        auto &[cannon, transform] = param;
        if (cannon.status == WaveCannon::Status::Firing) {
            instance.componentStorage.buildEntity()
                .withComponent(Sprite("effects", 22))
                .withComponent(Transform(transform))
                .withComponent(Velocity(5, 0))
                .build();
            cannon.status = WaveCannon::Status::Inactive;
        }
    }
}
