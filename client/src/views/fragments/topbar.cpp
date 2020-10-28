/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <iostream>
#include "views/fragments/topbar.hpp"
#include "views/fragments/inner/innertopbar.hpp"
#include "views/fragments/inner/innerbottombar.hpp"

TopBarFragment::TopBarFragment(std::optional<std::string> &view_intent, sf::RenderWindow &main_window) : Ifragment(view_intent, main_window)
{
    width = 600;
    height = 400;
    x = 700;
    y = 200;
    z_index = 10;
    background_color = sf::Color::Blue;
    add_fragment<InnerTopBarFragment>("innerTop");
    add_fragment<InnerBottomBarFragment>("innerBot");
}

void TopBarFragment::onCreateView()
{
    std::cout << "Create TopBar" << std::endl;
}

void TopBarFragment::onUpdateView()
{
    sf::CircleShape shape(200);
    shape.setFillColor(sf::Color(100, 250, 50));
    shape.setPosition(-100, -100);
    window.draw(shape);
}

void TopBarFragment::onFinishView()
{
    std::cout << "Finish TopBar" << std::endl;
}
