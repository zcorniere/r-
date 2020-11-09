#include "SfmlModule.hpp"
#include "SfmlKeyMapping.hpp"
#include <iostream>
#include <string_view>

SfmlModule::SfmlModule(const std::string &name, std::filesystem::path assets_path)
: m_window(sf::VideoMode(1000, 600), name), m_assets_path(assets_path)
{
    for (auto &file : std::filesystem::directory_iterator(m_assets_path)) {
        if (file.path().string().ends_with(".png"))
            loadAsset(file.path());
    }
}

void SfmlModule::loadAsset(std::filesystem::path path)
{
    sf::Texture texture;

    texture.loadFromFile(path);
    m_textures.emplace(path.stem(), std::move(texture));
    std::cout << "Loaded " << path.stem() << std::endl;
}

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
