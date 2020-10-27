/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <utility>
#include <SFML/Graphics.hpp>
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
sf_win(sf::VideoMode(1200, 800), "R-type")
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
    sf::Event event = {};
    while (sf_win.isOpen()) {
        sf_win.clear();
        view->onUpdateView();
        const auto intent = view->get_intent();
        if (intent != std::nullopt) {
            view->onFinishView();
            target_view = intent.value();
            view = views[target_view];
            view->onCreateView();
        }
        // TODO
        // Event handling
        while (sf_win.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                sf_win.close();
            }
        }
        sf_win.display();
    }
}


