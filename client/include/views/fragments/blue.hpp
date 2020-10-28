/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _TOPBAR_HPP_
#define _TOPBAR_HPP_

#include "components/interfaces/Ifragment.hpp"

class Blue : public Ifragment {
public:
    Blue(std::optional<std::string> &view_intent, bidimensional::Transform &parent_trans, sf::RenderWindow &main_window);
private:
    void onCreateView() final;
    void onUpdateView() final;
    void onFinishView() final;
};

#endif // _TOPBAR_HPP_