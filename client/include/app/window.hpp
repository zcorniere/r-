/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _SDK_WINDOW_HPP_
#define _SDK_WINDOW_HPP_

#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>
#include "sdk/interfaces/Iview.hpp"
#include "sdk/event.hpp"
#include "sdk/network.hpp"

namespace window {
    constexpr auto WIDTH = 1000;
    constexpr auto HEIGHT = 600;
    constexpr auto FRAMERATE = 60;
}

class Window {
    std::string target_view;
    Iview *view = nullptr;
    std::unordered_map<std::string, Iview *> views;
    sf::RenderWindow sf_win;
    Event event;
    Network network;
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

#endif