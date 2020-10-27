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

Window::Window(std::unordered_map<std::string, Iview *> &all_views, std::string default_view) : views(all_views), target_view(std::move(default_view))
{
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


