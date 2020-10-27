/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <utility>
#include "components/window.hpp"
#include "views/home.hpp"
#include "views/loading.hpp"

Window::Window(std::string default_view) : target_view(std::move(default_view))
{
    // list all views
    views.emplace("loading", new LoadingView);
    views.emplace("home", new HomeView);
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
    view->onUpdateView();
    const auto intent = view->get_intent();
    if (intent != std::nullopt) {
        view->onFinishView();
        target_view = intent.value();
        view = views[target_view];
        view->onCreateView();
    }
}


