/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <iostream>
#include "app/views/fragments/topbar.hpp"
#include "app/window.hpp"
#include "app/res/theme.hpp"

TopBar::TopBar(std::optional<std::string> &intent_ref, bidimensional::Transform &parent_trans, sf::RenderWindow &window) :
        Ifragment(intent_ref, parent_trans, window)
{
    constexpr auto barheight = 50;
    transform.position = {0, 0};
    transform.scale = {window::WIDTH, barheight};
    background_color = Theme().getSecondary().value();
}

void TopBar::onCreateView()
{
    std::cout << "Create Topbar" << std::endl;
}

void TopBar::onUpdateView()
{

}

void TopBar::onFinishView()
{
    std::cout << "Finish Topbar" << std::endl;
}

