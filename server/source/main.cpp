#include <iostream>
#include "Game.hpp"
#include "states/DebugState.hpp"
#include "Modules.hpp"
#include "interface/TcpServer.hpp"
#include "interface/UdpServer.hpp"
#include "GameServer.hpp"
#include "AssetsServer.hpp"

int main(void) {
    Game rtype("rtype 0.1");
    std::unique_ptr<AState> state(new DebugState);

    rtype.stateMachine.setState(std::move(state));
    rtype.run();
}
