/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <iostream>
#include "views/home.hpp"

HomeView::HomeView(sf::RenderWindow &window) : Iview(window)
{
        add_fragment<TopBarFragment>();
        add_fragment<BottomBarFragment>();
}

void HomeView::onCreateView()
{
    std::cout << "create home" << std::endl;
    helvetica.loadFromFile("assets/fonts/helvetica/helvetica.ttf");
    text.setFont(helvetica);
    text.setCharacterSize(12);
    text.setFillColor(sf::Color::Yellow);
    clock.restart();
}

void HomeView::onUpdateView()
{
    fps++;
    if (clock.getElapsedTime().asSeconds() >= 1) {
        text.setString("fps:" + std::to_string(fps));
        fps = 0;
        clock.restart();
    }
    window.draw(text);
}

void HomeView::onFinishView()
{
    std::cout << "finish home" << std::endl;
}
