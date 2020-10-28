/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <iostream>
#include "views/fragments/topbar.hpp"

TopBarFragment::TopBarFragment(std::optional<std::string> &view_intent, sf::RenderWindow &main_window) : Ifragment(view_intent, main_window)
{
    width = 600;
    height = 400;
    x = 300;
    y = 200;
    background_color = sf::Color::Blue;
}

void TopBarFragment::onCreateView()
{
    std::cout << "Create TopBar" << std::endl;
}

void TopBarFragment::onUpdateView()
{
    sf::CircleShape shape(200);
    shape.setFillColor(sf::Color(100, 250, 50));
    shape.setPosition(-100, -100);
    window.draw(shape);
}

void TopBarFragment::onFinishView()
{
    std::cout << "Finish TopBar" << std::endl;
}
