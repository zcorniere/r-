/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _SDK_WIDGETS_BUTTON_TEXT_HPP_
#define _SDK_WIDGETS_BUTTON_TEXT_HPP_

#include <functional>
#include <SFML/Graphics.hpp>
#include "sdk/interfaces/Iwidget.hpp"
#include "sdk/interfaces/Itheme.hpp"
#include "sdk/widgets/text.hpp"
#include "sdk/utils/varlock.hpp"
#include "sdk/managers/inputs.hpp"

class WidgetButtonText : public Iwidget {
    static constexpr auto padding_height = 5;
    static constexpr auto padding_width = 5;
    bool is_active = false;
    bool is_clicked = false;
    sdkutils::VarLock<sf::Cursor> arrow_curs;
    sdkutils::VarLock<sf::Cursor> pointer_curs;
    sf::Color base_color = sf::Color::Blue;
    sf::Color hover_color = sf::Color::White;
    sf::Color click_color = sf::Color::Yellow;
    sf::Color deactivate_color = sf::Color(170, 170, 170);
    // TODO border
    WidgetText *text;
    std::function<void(void)> handler;
    bool is_hover();
    void onCreateView() final;
    void onUpdateView() final;
    void onFinishView() final;
    void reload();
public:
    WidgetButtonText(std::optional<std::string> &view_intent, bidimensional::Transform &parent_trans, sf::RenderWindow &main_window, Itheme<Icolors *> *theme);
    void set_handler(std::function<void(void)> functor);
    void activate();
    void deactivate();
    void set_text(const std::string &newtext);
    void set_font(const std::string &path);
    void set_fontsize(unsigned int newsize);
    void set_color(sf::Color color);
    void set_background_color(sf::Color color);
    void set_hover_color(sf::Color color);
    void set_click_color(sf::Color color);
    void set_deactivate_color(sf::Color color);
    void click();
};

#endif