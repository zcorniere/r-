#include "SfmlModule.hpp"
#include "SfmlKeyMapping.hpp"

SfmlModule::SfmlModule(const std::string &name, Dimensional dimensions)
: m_window(sf::VideoMode(1000, 600), name)
{}

void SfmlModule::drawSprite(const std::string &name, Transform const &transform, unsigned id) {}

void SfmlModule::update()
{
    m_window.clear();
    m_window.display();
}

std::vector<Input> SfmlModule::getInputEvents()
{
    std::vector<Input> inputs;

    std::swap(inputs, m_pending_inputs);

    return inputs;
}

Dimensional SfmlModule::getCursorLocation()
{
    sf::Vector2i position = sf::Mouse::getPosition();

    return Dimensional{static_cast<float>(position.x),
                       static_cast<float>(position.y)};
}

void SfmlModule::retrieveInputs()
{
    sf::Event event;

    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_pending_inputs.push_back(Input::ExitWindow);
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Button::Left)
                m_pending_inputs.push_back(Input::LeftClick);
            if (event.mouseButton.button == sf::Mouse::Button::Right)
                m_pending_inputs.push_back(Input::RightClick);
        }
        if (event.type == sf::Event::KeyPressed)
            m_pending_inputs.push_back(sfml_key_mapping[event.key.code]);
    }
}

SfmlModule::~SfmlModule()
{
    m_window.close();
}
