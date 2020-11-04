/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _APP_VIEWS_HOME_HPP_
#define _APP_VIEWS_HOME_HPP_

#include "sdk/interfaces/Iview.hpp"

class HomeView : public Iview {
    void onCreateView() final;
    void onUpdateView() final;
    void onFinishView() final;
public:
    explicit HomeView(sf::RenderWindow &window);
};

#endif