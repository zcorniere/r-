/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _APP_VIEWS_FRAGMENTS_BOTTOMBAR_HPP_
#define _APP_VIEWS_FRAGMENTS_BOTTOMBAR_HPP_

#include "sdk/interfaces/Ifragment.hpp"

class BottomBar : public Ifragment {
    void onCreateView() final;
    void onUpdateView() final;
    void onFinishView() final;
public:
    BottomBar(std::optional<std::string> &intent_ref, bidimensional::Transform &parent_trans, sf::RenderWindow &window);
    static constexpr auto BARHEIGHT = 30;
};

#endif