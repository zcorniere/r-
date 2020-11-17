#include "components/PlayerShipController.hpp"
#include "components/Destructible.hpp"
#include "components/Sprite.hpp"
#include "Modules.hpp"

constexpr int TRANSITION_TICKS = 10;

void playership_animations(PlayerShipController &controller, Sprite &sprite)
{

    sprite.tile_id = controller.getPlayerId() * 10 + 2;
    sprite.tile_id +=
        controller.moovingUp +
        (controller.m_moovingUp_ticks >= TRANSITION_TICKS) +
        !controller.moovingUp * (controller.m_moovingUp_ticks > 0);
    sprite.tile_id -=
        controller.moovingDown +
        (controller.m_moovingDown_ticks >= TRANSITION_TICKS) +
        !controller.moovingDown * (controller.m_moovingDown_ticks > 0);

    controller.m_moovingUp_ticks +=
        (controller.moovingUp)
            ? 1 * (controller.m_moovingUp_ticks <= TRANSITION_TICKS)
            : -1 * (controller.m_moovingUp_ticks != 0);
    controller.m_moovingDown_ticks +=
        (controller.moovingDown)
            ? 1 * (controller.m_moovingDown_ticks <= TRANSITION_TICKS)
            : -1 * (controller.m_moovingDown_ticks != 0);
}

void playership_ct_input_getter(IInputModule &input,
                                PlayerShipController &controller,
                                const Destructible &destructible)
{
    if (destructible.status != Destructible::Status::Alive) {
        controller.moovingLeft = false;
        controller.moovingRight = false;
        controller.moovingUp = false;
        controller.moovingDown = false;
        controller.firing = false;
        return;
    }
    controller.moovingLeft = input.isKeyPressed(controller.getPlayerId(), Input::Left);
    controller.moovingRight = input.isKeyPressed(controller.getPlayerId(), Input::Right);
    controller.moovingUp = input.isKeyPressed(controller.getPlayerId(), Input::Up);
    controller.moovingDown = input.isKeyPressed(controller.getPlayerId(), Input::Down);
    controller.firing = input.isKeyPressed(controller.getPlayerId(), Input::Z);
}
