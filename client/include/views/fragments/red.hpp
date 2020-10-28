/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _BOTTOMBAR_HPP_
#define _BOTTOMBAR_HPP_

#include "components/interfaces/Ifragment.hpp"

class Red : public Ifragment {
public:
    Red(std::optional<std::string> &view_intent, sf::RenderWindow &main_window);
private:
    void onCreateView() final;
    void onUpdateView() final;
    void onFinishView() final;
};

#endif // _BOTTOMBAR_HPP_