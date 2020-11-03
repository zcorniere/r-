/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _APP_VIEWS_FRAGMENTS_GAME_HPP_
#define _APP_VIEWS_FRAGMENTS_GAME_HPP_

#include "sdk/interfaces/Ifragment.hpp"

class Game : public Ifragment {
    void onCreateView() final;
    void onUpdateView() final;
    void onFinishView() final;
public:
    Game(std::optional<std::string> &intent_ref, bidimensional::Transform &parent_trans, sf::RenderWindow &window);
};

#endif