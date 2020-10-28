/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <iostream>
#include "views/fragments/bottombar.hpp"

BottomBarFragment::BottomBarFragment(std::optional<std::string> &view_intent, sf::RenderWindow &main_window)
        : Ifragment(view_intent, main_window)
{
    width = 600;
    height = 400;
    x = 200;
    y = 100;
    z_index = 9;
    background_color = sf::Color::Red;
}

void BottomBarFragment::onCreateView()
{
    std::cout << "Create Bottombar" << std::endl;
}

void BottomBarFragment::onUpdateView()
{
    sf::CircleShape shape(50);
    shape.setFillColor(sf::Color::White);
    shape.setPosition(20, 20);
    window.draw(shape);
}

void BottomBarFragment::onFinishView()
{
    std::cout << "Finish Bottombar" << std::endl;
}
