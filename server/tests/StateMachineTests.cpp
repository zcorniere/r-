#include <iostream>
#include "StateMachine.hpp"

class BasicState : public AState {
public:
    void onStart() {}
    void onPause() {}
    void onResume() {}
    void onTick() {}
    void onStop() {}
};

int main(void)
{
    std::cout << "StateMachine tests...";

    BasicState state;
    BasicState state2;
    std::unique_ptr<AState> state3(new BasicState);
    StateMachine machine;

    if (state.getId() != 0 || state2.getId() != 1 || (*state3).getId() != 2) {
        std::cerr << std::endl << "Something is wrong with state Ids :/" << std::endl;
        return 1;
    }

    machine.getCurrentState();
    machine.setState(std::move(state3));
    machine.getCurrentState();
    if (machine.getCurrentState().value().get().getId() != 2) {
        std::cerr << std::endl << "Something is wrong with setState method" << std::endl;
        return 1;
    }

    std::cout << "Done !" << std::endl;
    return 0;
}
