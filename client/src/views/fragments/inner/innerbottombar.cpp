/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <iostream>
#include "views/fragments/inner/innerbottombar.hpp"

InnerBottomBarFragment::InnerBottomBarFragment(std::optional<std::string> &view_intent, sf::RenderWindow &main_window)
        : Ifragment(view_intent, main_window)
{
    width = 200;
    height = 200;
    x = 10;
    y = 10;
    z_index = 9;
    background_color = sf::Color::Green;
}

void InnerBottomBarFragment::onCreateView()
{
    std::cout << "Create Inner Bottombar" << std::endl;
}

void InnerBottomBarFragment::onUpdateView()
{
    sf::CircleShape shape(50);
    shape.setFillColor(sf::Color::White);
    shape.setPosition(20, 20);
    window.draw(shape);
}

void InnerBottomBarFragment::onFinishView()
{
    std::cout << "Finish Inner Bottombar" << std::endl;
}
