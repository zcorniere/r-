/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <iostream>
#include "app/views/fragments/bottombar.hpp"
#include "app/window.hpp"
#include "app/res/theme.hpp"

BottomBar::BottomBar(std::optional<std::string> &intent_ref, bidimensional::Transform &parent_trans, sf::RenderWindow &window) :
        Ifragment(intent_ref, parent_trans, window)
{
    constexpr auto barheight = 30;
    transform.position = {0, window::HEIGHT - barheight};
    transform.scale = {window::WIDTH, barheight};
    background_color = Theme().getSecondary().value();
}

void BottomBar::onCreateView()
{
    std::cout << "Create Bottombar" << std::endl;
}

void BottomBar::onUpdateView()
{

}

void BottomBar::onFinishView()
{
    std::cout << "Finish Bottombar" << std::endl;
}
