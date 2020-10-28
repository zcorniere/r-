/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>
#include "components/interfaces/Iview.hpp"
#include "components/event.hpp"
#include "components/network.hpp"

namespace window {
    constexpr auto WIDTH = 1200;
    constexpr auto HEIGHT = 800;
    constexpr auto FRAMERATE = 1000 / 60;
}

class Window {
    std::string target_view;
    Iview *view = nullptr;
    std::unordered_map<std::string, Iview *> views;
    sf::RenderWindow sf_win;
    Event event;
    Network network;
    sf::Clock clock;
public:
    /**
     * Window Ctor
     * @param default_view is the first view used by the client
     */
    explicit Window(std::string default_view = "loading");
    ~Window();

    /**
     * main update loop
     */
    void update();
};

#endif // _WINDOW_HPP_