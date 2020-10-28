/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <iostream>
#include "views/fragments/inner/green.hpp"

Green::Green(std::optional<std::string> &view_intent, bidimensional::Transform &parent_trans, sf::RenderWindow &main_window)
        : Ifragment(view_intent, parent_trans, main_window)
{
    transform.scale.x = 200;
    transform.scale.y = 200;
    transform.position.x = 0;
    transform.position.y = 0;
    z_index = 9;
    background_color = sf::Color::Green;
}

void Green::onCreateView()
{
    std::cout << "Create Inner Bottombar" << std::endl;
}

void Green::onUpdateView()
{
    sf::CircleShape shape(50);
    shape.setFillColor(sf::Color::White);
    shape.setPosition(20, 20);
    window.draw(shape);
}

void Green::onFinishView()
{
    std::cout << "Finish Inner Bottombar" << std::endl;
}
