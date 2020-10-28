/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _INNERBOTTOMBAR_HPP_
#define _INNERBOTTOMBAR_HPP_

#include "components/interfaces/Ifragment.hpp"

class InnerBottomBarFragment : public Ifragment {
public:
    InnerBottomBarFragment(std::optional<std::string> &view_intent, sf::RenderWindow &main_window);
private:
    void onCreateView() final;
    void onUpdateView() final;
    void onFinishView() final;
};

#endif // _INNERBOTTOMBAR_HPP_