/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _INNERTOPBAR_HPP_
#define _INNERTOPBAR_HPP_

#include "components/interfaces/Ifragment.hpp"

class Magenta : public Ifragment {
public:
    Magenta(std::optional<std::string> &view_intent, bidimensional::Transform &parent_trans, sf::RenderWindow &main_window);
private:
    void onCreateView() final;
    void onUpdateView() final;
    void onFinishView() final;
};

#endif // _INNERTOPBAR_HPP_