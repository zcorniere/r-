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
#include "sdk/managers/inputs.hpp"
#include "app/res/theme.hpp"
#include "app/res/string.hpp"
#include "app/window.hpp"
#include "app/views/home/home.hpp"
#include "app/views/loading/loading.hpp"

static std::unordered_map<std::string, std::function<std::unique_ptr<Iview>(void)>> generate_views(sf::RenderWindow &sf_win)
{
    std::unordered_map<std::string, std::function<std::unique_ptr<Iview>(void)>> ret;
    ret.emplace("loading", [&](){return std::make_unique<LoadingView>(sf_win);});
    ret.emplace("home", [&](){return std::make_unique<HomeView>(sf_win);});
    return ret;
}

Window::Window(std::string default_view) : target_view(std::move(default_view)),
    sf_win(sf::VideoMode(window::WIDTH, window::HEIGHT), "R-type", sf::Style::Titlebar | sf::Style::Close),
    event(sf_win)
{
    sf::Image icon;
    icon.loadFromFile(STRING("foxy_red_eye"));
    sf_win.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    sf_win.setFramerateLimit(window::FRAMERATE);
    Input().init(&event);
    views = generate_views(sf_win);
    // set the active view
    view = views[target_view]();
    view->runCreate();
}

Window::~Window()
{
    view->runFinish();
}

void Window::update()
{
    while (sf_win.isOpen()) {
        sf_win.clear(Theme().getPrimary().value());
        view->runUpdate();
        const auto intent = view->get_intent();
        if (intent != std::nullopt) {
            view->runFinish();
            view.reset();
            target_view = intent.value();
            view = views[target_view]();
            view->runCreate();
        }
        event.update();
        sf_win.display();
    }

}


