/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include "sdk/widgets/image.hpp"

WidgetImage::WidgetImage(std::optional<std::string> &view_intent, bidimensional::Transform &parent_trans, sf::RenderWindow &main_window, Itheme<Icolors *> *theme) :
    Iwidget(view_intent, parent_trans, main_window)
{
    transform.position = {100, 100};
    transform.scale = {100, 60};
    background_color = theme->getSecondary().value();
}

void WidgetImage::onCreateView()
{

}

void WidgetImage::onUpdateView()
{

}

void WidgetImage::onFinishView()
{

}
