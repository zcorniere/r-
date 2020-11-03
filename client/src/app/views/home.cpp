/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <iostream>
#include "sdk/widgets/image.hpp"
#include "app/res/string.hpp"
#include "app/res/theme.hpp"
#include "app/window.hpp"
#include "app/views/home.hpp"
#include "app/views/fragments/topbar.hpp"
#include "app/views/fragments/bottombar.hpp"
#include "app/views/fragments/game.hpp"

HomeView::HomeView(sf::RenderWindow &window) : Iview(window, {window::WIDTH, window::HEIGHT})
{
    add_fragment<TopBar>("Topbar");
    add_fragment<BottomBar>("BottomBar");
    add_fragment<Game>("GameScreen");
    // Adding foxy
    add_widget<WidgetImage>("foxy", reinterpret_cast<Itheme<Icolors *> *>(std::make_unique<Theme>().get()));
    auto foxy = get_fragment<WidgetImage>("foxy");
    foxy->set_img(STRING("foxy_head_trans_gray"));
    foxy->set_scale_bysize({200, 200});
    foxy->move({window::WIDTH / 2 - 100, window::HEIGHT / 2 - 150});
    foxy->z_index = 0;
}

void HomeView::onCreateView()
{
    std::cout << "create home" << std::endl;
}

void HomeView::onUpdateView()
{}

void HomeView::onFinishView()
{
    std::cout << "finish home" << std::endl;
}
