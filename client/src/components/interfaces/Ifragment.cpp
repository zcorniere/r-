/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include "components/interfaces/Ifragment.hpp"

void Ifragment::set_intent(const std::string &view)
{
    intent.emplace(view);
}

Ifragment::Ifragment(std::optional<std::string> &view_intent, sf::RenderWindow &main_window) :
        intent(view_intent), window(main_window)
{}

void Ifragment::runCreate()
{
    onCreateView();
    for (auto &fragment : fragments) {
        fragment->runCreate();
    }
}

void Ifragment::runUpdate()
{
    onUpdateView();
    for (auto &fragment : fragments) {
        fragment->runUpdate();
    }
}

void Ifragment::runFinish()
{
    for (auto &fragment : fragments) {
        fragment->runFinish();
    }
    onFinishView();
}
