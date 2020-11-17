#include "Modules.hpp"
#include "components/PlayerBarracks.hpp"
#include <iostream>

void player_barracks_filler(IInputModule &module, PlayerBarracks &barrack)
{
    if (!barrack.connectionsOpen)
        return;
    for (short i = 0; i < 4; i++) {
        if (!barrack.playerConnected[i] && module.isKeyPressed(i, Input::Z)) {
            barrack.playerConnected[i] = true;
            std::cout << "Player " << i << " joined !\n";
        }
    }
}
