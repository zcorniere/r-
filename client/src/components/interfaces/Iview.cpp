/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <algorithm>
#include "components/interfaces/Iview.hpp"
#include "components/window.hpp"

void Iview::set_intent(const std::string &view)
{
    intent.emplace(view);
}

Ifragment *Iview::get_fragment(const std::string &key)
{
    auto item = std::find_if(fragments.begin(), fragments.end(), [&](const auto &pair){
        return pair.first == key;
    });
    if (item == fragments.end())
        return nullptr;
    return item->second;
}

std::optional<std::string> Iview::get_intent()
{
    auto ret = intent;
    intent.reset();
    return ret;
}

Iview::Iview(sf::RenderWindow &main_window) :
    window(main_window)
{
    transform.scale.x = window::WIDTH;
    transform.scale.y = window::HEIGHT;
    transform.position.x = 0;
    transform.position.y = 0;
}

Iview::~Iview()
{
    for (auto &fragment : fragments) {
        delete fragment.second;
    }
}

void Iview::runCreate()
{
    // sort z_index
    std::sort(fragments.begin(), fragments.end(), [](const auto &left, const auto &right) {
        return left.second->z_index < right.second->z_index;
    });
    for (auto &fragment : fragments) {
        fragment.second->runCreate();
    }
    onCreateView();
}

void Iview::runUpdate()
{
    onUpdateView();
    for (auto &fragment : fragments) {
        fragment.second->runUpdate();
    }
    // the fragments edit the window view so after i need to reset it to default
    window.setView(window.getDefaultView());
}

void Iview::runFinish()
{
    for (auto &fragment : fragments) {
        fragment.second->runFinish();
    }
    onFinishView();
}


