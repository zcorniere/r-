/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _SDK_WIDGETS_IMAGE_HPP_
#define _SDK_WIDGETS_IMAGE_HPP_

#include <SFML/Graphics.hpp>
#include "sdk/interfaces/Iwidget.hpp"
#include "sdk/interfaces/Itheme.hpp"

class WidgetImage : public Iwidget {
    std::string image_path;
    sf::Texture texture;
    sf::Sprite sprite;
    bool use_default_size = true;
    sf::Vector2<float> default_size;
    void onCreateView() final;
    void onUpdateView() final;
    void onFinishView() final;
public:
    WidgetImage(std::optional<std::string> &view_intent, bidimensional::Transform &parent_trans, sf::RenderWindow &main_window, Itheme<Icolors *> *theme);
    /**
     * reload the image
     */
    void reload();
    void set_img(const std::string &path);
    void set_size(sf::Vector2<float> new_size);
    void set_scale(sf::Vector2<float> new_scale);
    void set_scale_bysize(sf::Vector2<float> size);
    void set_background(sf::Color);
};

#endif