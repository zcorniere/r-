/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _APP_VIEWS_FRAGMENTS_TOPBAR_HPP_
#define _APP_VIEWS_FRAGMENTS_TOPBAR_HPP_

#include <iostream>
#include "sdk/interfaces/Ifragment.hpp"
#include "sdk/widgets/text.hpp"
#include "sdk/widgets/text_entry.hpp"
#include "sdk/widgets/button_text.hpp"

class TopBar : public Ifragment {
    bool *is_connect = nullptr;
    void onCreateView() final;
    void onUpdateView() final;
    void onFinishView() final;
    WidgetText *text;
    WidgetButtonText *disconnect;
    WidgetButtonText *connect;
    WidgetText_entry *ip_entry;
    sf::Clock clock;
    unsigned fps = 0;
    sf::RectangleShape bottom_border;
public:
    static constexpr auto bar_height = 50;
    TopBar(std::optional<std::string> &intent_ref, bidimensional::Transform &parent_trans, sf::RenderWindow &window);
    void set_is_connect(bool *ptr);
};

#endif