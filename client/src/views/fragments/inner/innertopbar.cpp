/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <iostream>
#include "views/fragments/inner/innertopbar.hpp"

InnerTopBarFragment::InnerTopBarFragment(std::optional<std::string> &view_intent, sf::RenderWindow &main_window) : Ifragment(view_intent, main_window)
{
    width = 100;
    height = 100;
    x = 550;
    y = 50;
    z_index = 10;
    background_color = sf::Color::Black;
}

void InnerTopBarFragment::onCreateView()
{
    std::cout << "Create Inner TopBar" << std::endl;
}

void InnerTopBarFragment::onUpdateView()
{
    sf::CircleShape shape(10);
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(5, 5);
    window.draw(shape);
}

void InnerTopBarFragment::onFinishView()
{
    std::cout << "Finish Inner TopBar" << std::endl;
}
