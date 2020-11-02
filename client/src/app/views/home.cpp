/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <iostream>
#include "app/res/theme.hpp"
#include "app/views/home.hpp"
#include "app/res/string.hpp"
#include "app/window.hpp"

HomeView::HomeView(sf::RenderWindow &window) : Iview(window, {window::WIDTH, window::HEIGHT})
{
    add_widget<WidgetText>("text fps", reinterpret_cast<Itheme<Icolors *> *>(std::make_unique<Theme>().get()));
    text = get_fragment<WidgetText>("text fps");
    text->set_font(STRING("helvetica_font"));
    text->set_fontsize(15);
    text->set_color(sf::Color::Yellow);
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
        text->set_text("fps:" + std::to_string(fps));
        fps = 0;
        clock.restart();
    }
}

void HomeView::onFinishView()
{
    std::cout << "finish home" << std::endl;
}
