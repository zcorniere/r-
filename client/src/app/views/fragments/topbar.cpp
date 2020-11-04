/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <iostream>
#include "app/res/theme.hpp"
#include "app/res/string.hpp"
#include "app/window.hpp"
#include "app/views/fragments/topbar.hpp"

TopBar::TopBar(std::optional<std::string> &intent_ref, bidimensional::Transform &parent_trans, sf::RenderWindow &window) :
        Ifragment(intent_ref, parent_trans, window)
{
    transform.position = {0, 0};
    transform.scale = {window::WIDTH, BARHEIGHT};
    background_color = Theme().getSecondary().value();
    // add fps text
    add_widget<WidgetText>("text fps", reinterpret_cast<Itheme<Icolors *> *>(std::make_unique<Theme>().get()));
    text = get_fragment<WidgetText>("text fps");
    text->set_font(STRING("helvetica_font"));
    text->set_fontsize(15);
    text->set_color(sf::Color::Yellow);
    text->move({window::WIDTH - 50, 10});
    // add text_entry for ip
    add_widget<WidgetText_entry>("IP entry", reinterpret_cast<Itheme<Icolors *> *>(std::make_unique<Theme>().get()));
    ip_entry = get_fragment<WidgetText_entry>("IP entry");
    ip_entry->set_font(STRING("helvetica_font"));
    ip_entry->set_fontsize(15);
    ip_entry->set_color(Theme().getPrimary().value());
    ip_entry->set_background(Theme().getTertiary().value());
    ip_entry->move({200, 10});
    ip_entry->scale({400, 20});
    ip_entry->set_placeholder(STRING("IP_entry placeholder"));
    ip_entry->set_placeholder_color(Theme().getColor("Light Gray").value());
    ip_entry->set_maxchar_limit(40);
    ip_entry->set_handler([](std::string_view str){
        std::cout << "SUBMIT : " << str << std::endl;
    });
    clock.restart();
}

void TopBar::onCreateView()
{
    std::cout << "Create Topbar" << std::endl;
}

void TopBar::onUpdateView()
{
    fps++;
    if (clock.getElapsedTime().asSeconds() >= 1) {
        text->set_text("fps:" + std::to_string(fps));
        fps = 0;
        clock.restart();
    }
}

void TopBar::onFinishView()
{
    std::cout << "Finish Topbar" << std::endl;
}

