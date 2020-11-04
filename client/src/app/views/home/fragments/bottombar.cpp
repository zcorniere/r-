/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <iostream>
#include "app/res/theme.hpp"
#include "app/window.hpp"
#include "app/views/home/fragments/bottombar.hpp"

BottomBar::BottomBar(std::optional<std::string> &intent_ref, bidimensional::Transform &parent_trans, sf::RenderWindow &window) :
        Ifragment(intent_ref, parent_trans, window)
{
    transform.position = {0, window::HEIGHT - bar_height};
    transform.scale = {window::WIDTH, bar_height};
    background_color = Theme().getSecondary().value();
}

void BottomBar::onCreateView()
{
    std::cout << "Create Bottombar" << std::endl;
}

void BottomBar::onUpdateView()
{}

void BottomBar::onFinishView()
{
    std::cout << "Finish Bottombar" << std::endl;
}
