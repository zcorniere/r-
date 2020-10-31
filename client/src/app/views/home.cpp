/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <iostream>
#include "app/views/home.hpp"
#include "app/res/string.hpp"

HomeView::HomeView(sf::RenderWindow &window) : Iview(window)
{}

void HomeView::onCreateView()
{
    std::cout << "create home" << std::endl;
    helvetica.loadFromFile(ABS_PATH + "/assets/fonts/helvetica/helvetica.ttf");
    text.setFont(helvetica);
    text.setCharacterSize(12);
    text.setFillColor(sf::Color::Yellow);
    clock.restart();

    auto frag = get_fragment("Topbar");
    if (frag == nullptr) {
        std::cout << "Topbar fragment not founded" << std::endl;
    } else {
        std::cout << "Topbar fragment founded" << std::endl;
    }
    frag->move(700, 200, 10000);
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
