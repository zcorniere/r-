/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _LOADING_HPP_
#define _LOADING_HPP_

#include <SFML/Graphics.hpp>
#include "sdk/interfaces/Iview.hpp"

class LoadingView : public Iview {
    void onCreateView() final;
    void onUpdateView() final;
    void onFinishView() final;
    sf::Clock clock;
public:
    explicit LoadingView(sf::RenderWindow &window);
};

#endif