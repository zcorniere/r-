#include "Game.hpp"
#include "Snitch.hpp"
#include <stdexcept>

Game::Game(std::string name)
: m_name(name), stateMachine(*this), componentStorage(stateMachine)
{}

void Game::run()
{
    while(stateMachine.getCurrentState()) {
        stateMachine.update();
        for (auto &[name, module] : m_modules)
            (*module).update();
        systemStorage.runTick(*this);
    }
}

/*
    MODULES
*/

void Game::addModule(std::string name, std::unique_ptr<IModule> module)
{
    m_modules.emplace(std::move(name), std::move(module));
}

IModule &Game::getModule(const std::string &name)
{
    if (m_modules.find(name) != m_modules.end())
        return (*m_modules[name]);
    Snitch::warn() << "Module " << name << " isn't implemented in current instance" << Snitch::endl;
    throw std::runtime_error("Call to unexistant module");
}

// Specific Modules setters

void Game::setDisplayModule(const std::string &name)
{
    displayModule = dynamic_cast<IDisplayModule &>(getModule(name));
}

void Game::setInputModule(const std::string &name)
{
    inputModule = dynamic_cast<IInputModule &>(getModule(name));
}

void Game::setAudioModule(const std::string &name)
{
    audioModule = dynamic_cast<IAudioModule &>(getModule(name));
}

void Game::setNetworkModule(const std::string &name)
{
    networkModule = dynamic_cast<INetworkModule &>(getModule(name));
}
