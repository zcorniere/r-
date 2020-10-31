/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _SDK_WIDGETS_IMAGE_HPP_
#define _SDK_WIDGETS_IMAGE_HPP_

#include "sdk/interfaces/Iwidget.hpp"
#include "sdk/interfaces/Itheme.hpp"

class WidgetImage : public Iwidget {
public:
    WidgetImage(std::optional<std::string> &view_intent, bidimensional::Transform &parent_trans, sf::RenderWindow &main_window, Itheme<Icolors *> *theme);
private:
    void onCreateView() final;
    void onUpdateView() final;
    void onFinishView() final;
public:
};

#endif