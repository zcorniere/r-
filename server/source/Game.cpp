#include "Game.hpp"

Game::Game(std::string name) : m_name(name), stateMachine(*this)
{}

void Game::run()
{
    while(stateMachine.getCurrentState()) {
        stateMachine.update();
    }
}
