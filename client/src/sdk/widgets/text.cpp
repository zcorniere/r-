/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include "sdk/widgets/text.hpp"

WidgetText::WidgetText(std::optional<std::string> &view_intent, bidimensional::Transform &parent_trans, sf::RenderWindow &main_window, Itheme<Icolors *> *theme) :
        Iwidget(view_intent, parent_trans, main_window)
{
    text.setCharacterSize(12);
    background_color = theme->getColor("Transparent").value();
    reload();
}

void WidgetText::onCreateView()
{}

void WidgetText::onUpdateView()
{
    window.draw(text);
}

void WidgetText::onFinishView()
{}

void WidgetText::reload()
{
    const unsigned charsize = text.getCharacterSize();
    const unsigned letterspacing = text.getLetterSpacing();
    const unsigned offset = charsize + letterspacing;
    const std::string str = text.getString();
    size = {
            static_cast<float>(str.length() * (offset / 2 + text_padding_width)),
            static_cast<float>(charsize) + text_padding_height
    };
    scale(size);
}

void WidgetText::set_font(const std::string &path)
{
    font.loadFromFile(path);
    text.setFont(font);
}

void WidgetText::set_fontsize(unsigned int newsize)
{
    text.setCharacterSize(newsize);
    reload();
}

void WidgetText::set_color(sf::Color color)
{
    text.setFillColor(color);
}

void WidgetText::set_text(const std::string &newtext)
{
    text.setString(newtext);
    reload();
}

void WidgetText::set_background(sf::Color color)
{
    background_color = color;
}

sf::Vector2<float> WidgetText::get_size() const
{
    return size;
}
