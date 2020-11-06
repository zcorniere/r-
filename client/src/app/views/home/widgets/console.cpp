/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include "app/views/home/fragments/bottombar.hpp"
#include "app/views/home/widgets/console.hpp"

Console::Console(std::optional<std::string> &view_intent, bidimensional::Transform &parent_trans, sf::RenderWindow &main_window, Itheme<Icolors *> *theme) :
    Iwidget(view_intent, parent_trans, main_window)
{
//    transform.position = {console_width_offset, window::HEIGHT - BottomBar::bar_height - transform.scale.y + console_height_offset};
    auto color = theme->getColor("Black").value();
    color.a /= 2;
    background_color = color;
    border.setOutlineColor(theme->getColor("Black").value());
    border.setFillColor(theme->getColor("Transparent").value());
    border.setOutlineThickness(border_thickness);
    set_fold_pos({window::WIDTH / 2 + padding_left, window::HEIGHT - BottomBar::bar_height + margin_height});
    set_unfold_pos({fold_pos.x, fold_pos.y - unfold_size.y + fold_size.y });
    reload();
}

void Console::onCreateView()
{}

void Console::onUpdateView()
{
    window.draw(border);
}

void Console::onFinishView()
{}

void Console::set_fold_pos(sf::Vector2<float> newpos)
{
    fold_pos = newpos;
}

void Console::set_fold_size(sf::Vector2<float> newsize)
{
    fold_size = newsize;
}

void Console::set_unfold_pos(sf::Vector2<float> newpos)
{
    unfold_pos = newpos;
}

void Console::set_unfold_size(sf::Vector2<float> newsize)
{
    unfold_size = newsize;
}

void Console::reload()
{
    if (is_fold) {
        move(fold_pos);
        scale(fold_size);
    } else {
        move(unfold_pos);
        scale(unfold_size);
    }
    border.setPosition({border_thickness, border_thickness});
    border.setSize({transform.scale.x - border_thickness * 2, transform.scale.y - border_thickness * 2});
}


void Console::fold()
{
    is_fold = true;
    reload();
}

void Console::unfold()
{
    is_fold = false;
    reload();
}

void Console::flip()
{
    if (is_fold) {
        unfold();
    } else {
        fold();
    }
}
