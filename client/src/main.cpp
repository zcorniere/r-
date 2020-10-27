/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <iostream>
#include <unordered_map>
#include <string>
#include "components/interfaces/Iview.hpp"
#include "views/loading.hpp"
#include "views/home.hpp"
#include "components/window.hpp"

static std::unordered_map<std::string, Iview *> generate_views()
{
    std::unordered_map<std::string, Iview *> ret;
    ret.emplace("loading", new LoadingView);
    ret.emplace("home", new HomeView);
    return ret;
}

int main() {
    auto views = generate_views();
    Window win(views);
    win.update();
    return 0;
}
