#include "Game.hpp"
#include "states/DebugState.hpp"
#include <iostream>

int main(void) {
    Game rtype("rtype 0.1");
    std::unique_ptr<AState> state(new DebugState);

    rtype.stateMachine.setState(std::move(state));
    rtype.run();
}
