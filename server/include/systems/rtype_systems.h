#ifndef RTYPE_SYSTEMS_H
#define RTYPE_SYSTEMS_H

#include "components/PlayerShipController.hpp"

void collisions_system(Game &instance);
void playership_ct_input_getter(IInputModule &input, PlayerShipController &controller);
void playership_animations(const PlayerShipController &controller, Sprite &sprite);

#endif
