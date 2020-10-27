/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <iostream>
#include "views/loading.hpp"

void LoadingView::onCreateView()
{
    std::cout << "create loading" << std::endl;
}

void LoadingView::onUpdateView()
{
    static unsigned long i = 0;

    sf::CircleShape shape(50);
    shape.setFillColor(sf::Color(100, 250, 50));
    shape.setPosition(500, 500);
    window.draw(shape);

    if (i != 9000000000) {
        set_intent("home");
    }
}

void LoadingView::onFinishView()
{
    std::cout << "finish loading" << std::endl;
}