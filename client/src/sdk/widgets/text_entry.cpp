/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include "sdk/widgets/text_entry.hpp"

WidgetText_entry::WidgetText_entry(std::optional<std::string> &view_intent, bidimensional::Transform &parent_trans, sf::RenderWindow &main_window, Itheme<Icolors *> *theme) :
    Iwidget(view_intent, parent_trans, main_window)
{

}

void WidgetText_entry::onCreateView()
{

}

void WidgetText_entry::onUpdateView()
{

}

void WidgetText_entry::onFinishView()
{

}

void WidgetText_entry::reload()
{

}

void WidgetText_entry::set_font(const std::string &path)
{
    text->set_font(path);
}

void WidgetText_entry::set_fontsize(unsigned int newsize)
{
    text->set_fontsize(newsize);
}

void WidgetText_entry::set_color(sf::Color color)
{
    text->set_color(color);
}

void WidgetText_entry::set_background(sf::Color color)
{
    background_color = color;
    text->set_background(color);
}

void WidgetText_entry::set_handler(void (*func)(const std::string &))
{
    handler = func;
}
