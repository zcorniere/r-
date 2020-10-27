/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include "components/event.hpp"

void Event::update() {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}
