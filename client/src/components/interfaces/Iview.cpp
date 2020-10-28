/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include "components/interfaces/Iview.hpp"

void Iview::set_intent(const std::string &view)
{
    intent.emplace(view);
}

std::optional<std::string> Iview::get_intent()
{
    auto ret = intent;
    intent.reset();
    return ret;
}

Iview::Iview(sf::RenderWindow &main_window) :
    window(main_window)
{}

Iview::~Iview()
{
    for (auto &fragment : fragments) {
        delete fragment;
    }
}

void Iview::runCreate()
{
    // sort z_index
    std::sort(fragments.begin(), fragments.end(), [](const auto &left, const auto &right) {
        return left->z_index < right->z_index;
    });
    onCreateView();
    for (auto &fragment : fragments) {
        fragment->runCreate();
    }
}

void Iview::runUpdate()
{
    onUpdateView();
    for (auto &fragment : fragments) {
        fragment->runUpdate();
    }
    // the fragment edit the view so after i need to reset it to defau
    window.setView(window.getDefaultView());
}

void Iview::runFinish()
{
    for (auto &fragment : fragments) {
        fragment->runFinish();
    }
    onFinishView();
}

