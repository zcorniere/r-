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

void Iview::runCreate()
{
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
}

void Iview::runFinish()
{
    for (auto &fragment : fragments) {
        fragment->runFinish();
    }
    onFinishView();
}