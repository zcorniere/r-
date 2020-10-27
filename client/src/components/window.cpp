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
    sf_win(sf::VideoMode(1200, 800), "R-type"),
    event(sf_win)
{
    views = generate_views(sf_win);
    // set the active view
    view = views[target_view];
    view->onCreateView();
}

Window::~Window()
{
    view->onFinishView();
}

void Window::update()
{
    while (sf_win.isOpen()) {
        const auto elapsed = clock.getElapsedTime().asMilliseconds();
        if (elapsed < time_per_tick) {
            std::this_thread::sleep_for(std::chrono::milliseconds(time_per_tick - elapsed));
        }
        clock.restart();
        sf_win.clear();
        view->onUpdateView();
        const auto intent = view->get_intent();
        if (intent != std::nullopt) {
            view->onFinishView();
            target_view = intent.value();
            view = views[target_view];
            view->onCreateView();
        }
        event.update();
        network.update();
        sf_win.display();
    }
}


