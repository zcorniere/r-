/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _SDK_WIDGETS_TEXT_ENTRY_HPP_
#define _SDK_WIDGETS_TEXT_ENTRY_HPP_

#include <SFML/Graphics.hpp>
#include "sdk/interfaces/Iwidget.hpp"
#include "sdk/interfaces/Itheme.hpp"
#include "sdk/widgets/text.hpp"

class WidgetText_entry : public Iwidget {
    sf::Vector2<float> size;
    WidgetText *text = nullptr;
    std::string data = "";
    void (*handler)(const std::string &text) = nullptr;
    void onCreateView() final;
    void onUpdateView() final;
    void onFinishView() final;
    void reload();
public:
    WidgetText_entry(std::optional<std::string> &view_intent, bidimensional::Transform &parent_trans, sf::RenderWindow &main_window, Itheme<Icolors *> *theme);
    void set_font(const std::string &path);
    void set_fontsize(unsigned int newsize);
    void set_color(sf::Color color);
    void set_background(sf::Color color);
    void set_handler(void (*handler)(const std::string &text));
};

#endif