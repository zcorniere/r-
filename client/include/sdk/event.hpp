/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _SDK_EVENT_HPP_
#define _SDK_EVENT_HPP_

#include <SFML/Graphics.hpp>

class Event {
    sf::RenderWindow &window;
    sf::Event event = {};
public:
    explicit Event(sf::RenderWindow &sf_win) : window(sf_win) {}
    void update();
};

#endif