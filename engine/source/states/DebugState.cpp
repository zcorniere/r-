#include "states/DebugState.hpp"
#include "Game.hpp"
#include <iostream>

DebugState::DebugState() : m_tickCounter(0), AState()
{}

void DebugState::onStart(Game &instance)
{
    Snitch::info() << "[" << getId() << "] Started !" << Snitch::endl;
}

void DebugState::onPause(Game &instance)
{
    Snitch::info() << "[" << getId() << "] Paused !" << Snitch::endl;
}

void DebugState::onResume(Game &instance)
{
    Snitch::info() << "[" << getId() << "] Resumed !" << Snitch::endl;
}

void DebugState::onTick(Game &instance)
{
    Snitch::info() << "[" << getId() << "] Ticked !" << Snitch::endl;
    if (m_tickCounter == 5 && getId() == 0) {
        Snitch::info() << "[" << getId() << "] I'm dying.., 2 pls take my place now" << Snitch::endl;
        std::unique_ptr<AState> state2(new DebugState);
        instance.stateMachine.setState(std::move(state2));
    }
    if (m_tickCounter == 2 && getId() == 0) {
        Snitch::info() << "[" << getId() << "] Okay 1, take my place for a few turns please !" << Snitch::endl;
        std::unique_ptr<AState> state1(new DebugState);
        instance.stateMachine.stackState(std::move(state1));
    }
    if (m_tickCounter == 2 && getId() == 1) {
        Snitch::info() << "[" << getId() << "] I'm dying..., take your turn back 0 !" << Snitch::endl;
        instance.stateMachine.leaveCurrentState();
    }
    if (m_tickCounter == 2 && getId() == 2) {
        Snitch::info() << "[" << getId() << "] I'm dying too... this is the end of it all..." << Snitch::endl;
        instance.stateMachine.leaveCurrentState();
    }
    m_tickCounter++;
}

void DebugState::onStop(Game &instance)
{
    Snitch::info() << "[" << getId() << "] Stopped !" << Snitch::endl;
}
