#ifndef PLAYER_BARRACKS_HPP
#define PLAYER_BARRACKS_HPP

#include <vector>

struct PlayerBarracks {
    bool connectionsOpen = true;
    bool autoRespawn = false;
    std::vector<bool> playerConnected = {false, false, false, false};
    std::vector<bool> playerAlive = {true, true, true, true};
};

#endif
