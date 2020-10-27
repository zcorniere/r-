/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <iostream>
#include "views/home.hpp"

void HomeView::onCreateView()
{
    std::cout << "create home" << std::endl;
}

void HomeView::onUpdateView()
{
    sf::CircleShape shape(20);
    shape.setFillColor(sf::Color(250, 100, 50));
    shape.setPosition(300, 300);
    window.draw(shape);
}

void HomeView::onFinishView()
{
    std::cout << "finish home" << std::endl;
}
