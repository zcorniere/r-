/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include "app/res/colors.hpp"

Colors::Colors() : Icolors()
{
    list.emplace("Black", sf::Color::Black);
    list.emplace("White", sf::Color::White);
    list.emplace("Red", sf::Color::Red);
    list.emplace("Green", sf::Color::Green);
    list.emplace("Blue", sf::Color::Blue);
    list.emplace("Yellow", sf::Color::Yellow);
    list.emplace("Magenta", sf::Color::Magenta);
    list.emplace("Cyan", sf::Color::Cyan);
    list.emplace("Transparent", sf::Color::Transparent);
}