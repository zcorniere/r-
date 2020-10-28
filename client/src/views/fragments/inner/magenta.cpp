/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <iostream>
#include "views/fragments/inner/magenta.hpp"

Magenta::Magenta(std::optional<std::string> &view_intent, bidimensional::Transform &parent_trans, sf::RenderWindow &main_window) :
    Ifragment(view_intent, parent_trans, main_window)
{
    transform.scale.x = 200;
    transform.scale.y = 200;
    transform.position.x = 450;
    transform.position.y = 250;
    z_index = 10;
    background_color = sf::Color::Magenta;
}

void Magenta::onCreateView()
{
    std::cout << "Create Inner TopBar" << std::endl;
}

void Magenta::onUpdateView()
{
    sf::CircleShape shape(10);
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(5, 5);
    window.draw(shape);
}

void Magenta::onFinishView()
{
    std::cout << "Finish Inner TopBar" << std::endl;
}
