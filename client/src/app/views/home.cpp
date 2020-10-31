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
}

void HomeView::onCreateView()
{
    std::cout << "create home" << std::endl;
    helvetica.loadFromFile(ABS_PATH + "/assets/fonts/helvetica/helvetica.ttf");
    text.setFont(helvetica);
    text.setCharacterSize(12);
    text.setFillColor(sf::Color::Yellow);
    clock.restart();

    auto frag = get_fragment("Image");
    if (frag == nullptr) {
        std::cout << "fragment not founded" << std::endl;
    } else {
        std::cout << "fragment founded" << std::endl;
    }
    // frag->move(700, 200, 10000);
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
