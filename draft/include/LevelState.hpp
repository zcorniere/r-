#ifndef LEVEL_STATE_HPP
#define LEVEL_STATE_HPP

#include "StateMachine.hpp"

class LevelState : public AState {
public:
    void onStart(Game &instance) override;
    void onPause(Game &instance) override;
    void onResume(Game &instance) override;
    void onTick(Game &instance) override;
    void onStop(Game &instance) override;
};

#endif
