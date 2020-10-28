/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <iostream>
#include "views/fragments/blue.hpp"
#include "views/fragments/inner/magenta.hpp"
#include "views/fragments/inner/green.hpp"

Blue::Blue(std::optional<std::string> &view_intent, bidimensional::Transform &parent_trans, sf::RenderWindow &main_window) :
    Ifragment(view_intent, parent_trans, main_window)
{
    transform.scale.x = 600;
    transform.scale.y = 400;
    transform.position.x = -50;
    transform.position.y = -50;
    z_index = 10;
    background_color = sf::Color::Blue;
    add_fragment<Magenta>("innerTop");
    add_fragment<Green>("innerBot");
}

void Blue::onCreateView()
{
    std::cout << "Create TopBar" << std::endl;
}

void Blue::onUpdateView()
{
    sf::CircleShape shape(200);
    shape.setFillColor(sf::Color(100, 250, 50));
    shape.setPosition(-100, -100);
    window.draw(shape);
}

void Blue::onFinishView()
{
    std::cout << "Finish TopBar" << std::endl;
}
