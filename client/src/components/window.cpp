/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <utility>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include "components/window.hpp"
#include "views/home.hpp"
#include "views/loading.hpp"

static std::unordered_map<std::string, Iview *> generate_views(sf::RenderWindow &sf_win)
{
    std::unordered_map<std::string, Iview *> ret;
    ret.emplace("loading", new LoadingView(sf_win));
    ret.emplace("home", new HomeView(sf_win));
    return ret;
}

Window::Window(std::string default_view) : target_view(std::move(default_view)),
    sf_win(sf::VideoMode(window::WIDTH, window::HEIGHT), "R-type", sf::Style::Titlebar | sf::Style::Close),
    event(sf_win)
{
    // TODO sf_win.setIcon()
    // TODO sf_win.setFramerateLimit()
    views = generate_views(sf_win);
    // set the active view
    view = views[target_view];
    view->runCreate();
}

Window::~Window()
{
    view->runFinish();
    for (auto &itemview : views) {
        delete itemview.second;
    }
}

void Window::update()
{
    while (sf_win.isOpen()) {
        const auto elapsed = clock.getElapsedTime().asMilliseconds();
        if (elapsed < window::FRAMERATE) {
            std::this_thread::sleep_for(std::chrono::milliseconds(window::FRAMERATE - elapsed));
        }
        clock.restart();
        sf_win.clear();
        view->runUpdate();
        const auto intent = view->get_intent();
        if (intent != std::nullopt) {
            view->runFinish();
            target_view = intent.value();
            view = views[target_view];
            view->runCreate();
        }
        event.update();
        network.update();
        sf_win.display();
    }
}


