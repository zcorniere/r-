#include "SfmlModule.hpp"

SfmlModule::SfmlModule(const std::string &name, Dimensional dimensions)
: m_window(sf::VideoMode(1000, 600), name)
{}

void SfmlModule::drawSprite(const std::string &name, Transform const &transform, unsigned id) {}

void SfmlModule::update()
{
    m_window.clear();
    m_window.display();
}

SfmlModule::~SfmlModule()
{
    m_window.close();
}
