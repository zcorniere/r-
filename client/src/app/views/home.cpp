/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <iostream>
#include <memory>
#include "sdk/widgets/image.hpp"
#include "app/views/home.hpp"
#include "app/res/string.hpp"
#include "app/res/theme.hpp"

HomeView::HomeView(sf::RenderWindow &window) : Iview(window)
{
    add_fragment<WidgetImage>("Image", reinterpret_cast<Itheme<Icolors *> *>(std::make_unique<Theme>().get()));
    auto frag = get_fragment<WidgetImage>("Image");
    frag->set_img(STRING("foxy_head_trans_coffe"));
    frag->set_scale_bysize({300, 300});
    frag->move({0, 0});
}

void HomeView::onCreateView()
{
    std::cout << "create home" << std::endl;
    helvetica.loadFromFile(STRING("helvetica_font"));
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
