/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _APP_VIEWS_FRAGMENTS_TOPBAR_HPP_
#define _APP_VIEWS_FRAGMENTS_TOPBAR_HPP_

#include "sdk/interfaces/Ifragment.hpp"
#include "sdk/widgets/text.hpp"

class TopBar : public Ifragment {
    void onCreateView() final;
    void onUpdateView() final;
    void onFinishView() final;
    WidgetText *text;
    sf::Clock clock;
    unsigned fps = 0;
public:
    TopBar(std::optional<std::string> &intent_ref, bidimensional::Transform &parent_trans, sf::RenderWindow &window);
    static constexpr auto BARHEIGHT = 50;
};

#endif