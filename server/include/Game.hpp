#ifndef GAME_HPP
#define GAME_HPP

#include "StateMachine.hpp"
#include "ComponentStorage.hpp"
#include <string>

class Game {
private:
    std::string m_name;
public:
    StateMachine stateMachine;
    ComponentStorage componentStorage;
public:
    Game(std::string name);
    void run();
};

#endif
