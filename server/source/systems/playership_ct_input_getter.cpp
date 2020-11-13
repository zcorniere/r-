#include "components/PlayerShipController.hpp"
#include "Modules.hpp"

void playership_ct_input_getter(IInputModule &input, PlayerShipController &controller)
{
    controller.moovingLeft = input.isKeyPressed(controller.getPlayerId(), Input::Left);
    controller.moovingRight = input.isKeyPressed(controller.getPlayerId(), Input::Right);
    controller.moovingUp = input.isKeyPressed(controller.getPlayerId(), Input::Up);
    controller.moovingDown = input.isKeyPressed(controller.getPlayerId(), Input::Down);
    controller.firing = input.isKeyPressed(controller.getPlayerId(), Input::Z);
}
