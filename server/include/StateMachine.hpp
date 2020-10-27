#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include <stack>
#include <memory>
#include <optional>
#include <vector>
#include <functional>

class AState {
private:
    short m_id;
    static short m_stateCount;
public:
    AState();
    short getId();
    virtual void onStart() = 0;
    virtual void onPause() = 0;
    virtual void onResume() = 0;
    virtual void onTick() = 0;
    virtual void onStop() = 0;
};

class StateMachine {
private:
    std::stack<std::unique_ptr<AState>> m_statesStack;
public:
    StateMachine();
    void setState(std::unique_ptr<AState> &state);
    void stackState(std::unique_ptr<AState> &state);
    std::optional<std::reference_wrapper<AState>> getCurrentState() const;
    void leaveCurrentState();
};

#endif
