/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <iostream>
#include "app/views/home.hpp"
#include "app/res/string.hpp"
#include "app/window.hpp"

HomeView::HomeView(sf::RenderWindow &window) : Iview(window, {window::WIDTH, window::HEIGHT})
{
    helvetica.loadFromFile(STRING("helvetica_font"));
    text.setFont(helvetica);
    text.setCharacterSize(12);
    text.setFillColor(sf::Color::Yellow);
    clock.restart();
}

void HomeView::onCreateView()
{
    std::cout << "create home" << std::endl;
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
