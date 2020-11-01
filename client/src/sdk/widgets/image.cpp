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
    background_color = theme->getColor("Transparent").value();
}

void WidgetImage::onCreateView()
{}

void WidgetImage::onUpdateView()
{
    window.draw(sprite);
}

void WidgetImage::onFinishView()
{}

void WidgetImage::reload()
{
    if (!image_path.empty()) {
        texture.loadFromFile(image_path);
        default_size = {static_cast<float>(texture.getSize().x), static_cast<float>(texture.getSize().y)};
        if (use_default_size)
            transform.scale = default_size;
        sprite.setTexture(texture);
    }
}

void WidgetImage::set_img(const std::string &path)
{
    image_path = path;
    reload();
}

void WidgetImage::set_size(sf::Vector2<float> new_size)
{
    use_default_size = false;
    transform.scale = new_size;
    reload();
}

void WidgetImage::set_scale(sf::Vector2<float> new_scale)
{
    sprite.scale(new_scale);
    reload();
}

void WidgetImage::set_scale_bysize(sf::Vector2<float> size)
{
    const auto x = size.x / default_size.x;
    const auto y = size.y / default_size.y;
    set_scale({x, y});
    set_size(size);
}

void WidgetImage::set_background(sf::Color color)
{
    background_color = color;
    reload();
}




