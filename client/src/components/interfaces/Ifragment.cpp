/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include "components/window.hpp"
#include "components/interfaces/Ifragment.hpp"

void Ifragment::set_intent(const std::string &view)
{
    intent.emplace(view);
}

Ifragment::Ifragment(std::optional<std::string> &view_intent, sf::RenderWindow &main_window) :
        intent(view_intent), window(main_window)
{}

Ifragment::~Ifragment()
{
    for (auto &fragment : fragments) {
        delete fragment;
    }
}

void Ifragment::runCreate()
{
    content.setCenter(width / 2, height / 2);
    content.setSize(width, height);
    const auto posx_percent = 1 / (window::WIDTH / x);
    const auto posy_percent = 1 / (window::HEIGHT / y);
    const auto width_percent = 1 / (window::WIDTH / width);
    const auto height_percent = 1 / (window::HEIGHT / height);
    content.setViewport(sf::FloatRect(posx_percent, posy_percent, width_percent, height_percent));
    // background
    background.setFillColor(background_color);
    background.setSize(sf::Vector2f(width, height));
    background.setPosition(0, 0);
    // sort z_index
    std::sort(fragments.begin(), fragments.end(), [](const auto &left, const auto &right) {
        return left->z_index < right->z_index;
    });
    onCreateView();
    for (auto &fragment : fragments) {
        fragment->runCreate();
    }
}

void Ifragment::runUpdate()
{
    window.setView(content);
    window.draw(background);
    onUpdateView();
    for (auto &fragment : fragments) {
        fragment->runUpdate();
    }
}

void Ifragment::runFinish()
{
    for (auto &fragment : fragments) {
        fragment->runFinish();
    }
    onFinishView();
}
