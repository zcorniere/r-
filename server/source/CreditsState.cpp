#include "Game.hpp"
#include "CreditsState.hpp"
#include "components/Sprite.hpp"
#include "components/Transform.hpp"
#include "components/Velocity.hpp"
#include "components/Lifetime.hpp"
#include "components/DeathRattle.hpp"

void CreditsState::onStart(Game &instance)
{
    instance.componentStorage.buildEntity()
        .withComponent(Sprite("space_background", 0))
        .withComponent(Transform({0,0}, {0,0}, {1800, 960}))
        .build();

    instance.componentStorage.buildEntity()
        .withComponent(Sprite("credits"), 0)
        .withComponent(Transform({0, -1000}, {0, 0}, {1, 1}))
        .withComponent(Velocity({0, 1}))
        .build();
}

void CreditsState::onPause(Game &instance)
{}

void CreditsState::onResume(Game &instance)
{}

void CreditsState::onTick(Game &instance)
{}

void CreditsState::onStop(Game &instance)
{}
