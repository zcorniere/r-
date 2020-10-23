#include "StateMachine.hpp"

short AState::m_stateCount = 0;

// AState methods

AState::AState() : m_id(AState::m_stateCount++)
{}

short AState::getId()
{
    return m_id;
}

// StateMachine methods

StateMachine::StateMachine()
{}

void StateMachine::setState(std::unique_ptr<AState> &state)
{
    leaveCurrentState();
    stackState(state);
}

void StateMachine::stackState(std::unique_ptr<AState> &state)
{
    m_statesStack.push(std::move(state));
}

std::optional<std::reference_wrapper<AState>> StateMachine::getCurrentState()
{
    if (!m_statesStack.empty())
        return *(m_statesStack.top());
    return {};
}

void StateMachine::leaveCurrentState()
{
    if (!m_statesStack.empty())
        m_statesStack.pop();
}
