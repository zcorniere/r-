/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <iostream>
#include "app/res/theme.hpp"
#include "app/res/string.hpp"
#include "app/window.hpp"
#include "app/views/fragments/topbar.hpp"

TopBar::TopBar(std::optional<std::string> &intent_ref, bidimensional::Transform &parent_trans, sf::RenderWindow &window) :
        Ifragment(intent_ref, parent_trans, window)
{
    transform.position = {0, 0};
    transform.scale = {window::WIDTH, BARHEIGHT};
    background_color = Theme().getSecondary().value();
    add_widget<WidgetText>("text fps", reinterpret_cast<Itheme<Icolors *> *>(std::make_unique<Theme>().get()));
    text = get_fragment<WidgetText>("text fps");
    text->set_font(STRING("helvetica_font"));
    text->set_fontsize(15);
    text->set_color(sf::Color::Yellow);
    text->move({window::WIDTH - 50, 10});
    clock.restart();
}

void TopBar::onCreateView()
{
    std::cout << "Create Topbar" << std::endl;
}

void TopBar::onUpdateView()
{
    fps++;
    if (clock.getElapsedTime().asSeconds() >= 1) {
        text->set_text("fps:" + std::to_string(fps));
        fps = 0;
        clock.restart();
    }
}

void TopBar::onFinishView()
{
    std::cout << "Finish Topbar" << std::endl;
}

