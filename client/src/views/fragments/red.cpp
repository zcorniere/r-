/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <iostream>
#include "views/fragments/red.hpp"

Red::Red(std::optional<std::string> &view_intent, bidimensional::Transform &parent_trans, sf::RenderWindow &main_window)
        : Ifragment(view_intent, parent_trans, main_window)
{
    transform.scale.x = 600;
    transform.scale.y = 400;
    transform.position.x = 200;
    transform.position.y = 100;
    z_index = 9;
    background_color = sf::Color::Red;
}

void Red::onCreateView()
{
    std::cout << "Create Bottombar" << std::endl;
}

void Red::onUpdateView()
{
    sf::CircleShape shape(50);
    shape.setFillColor(sf::Color::White);
    shape.setPosition(20, 20);
    window.draw(shape);
}

void Red::onFinishView()
{
    std::cout << "Finish Bottombar" << std::endl;
}
