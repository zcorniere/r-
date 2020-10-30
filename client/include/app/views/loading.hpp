/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _LOADING_HPP_
#define _LOADING_HPP_

#include "sdk/interfaces/Iview.hpp"

class LoadingView : public Iview {
public:
    explicit LoadingView(sf::RenderWindow &window) : Iview(window) {};
private:
    void onCreateView() final;
    void onUpdateView() final;
    void onFinishView() final;
};

#endif // _LOADING_HPP_