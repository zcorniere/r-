/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include "sdk/widgets/text_entry.hpp"

static void setup_ignored_keys(std::vector<keyboard::Key> &ignored_keys)
{
    ignored_keys.push_back(keyboard::Key::LeftClick);
    ignored_keys.push_back(keyboard::Key::RightClick);
}

WidgetText_entry::WidgetText_entry(std::optional<std::string> &view_intent, bidimensional::Transform &parent_trans, sf::RenderWindow &main_window, Itheme<Icolors *> *theme) :
    Iwidget(view_intent, parent_trans, main_window)
{
    add_widget<WidgetText>("text", theme);
    text = get_fragment<WidgetText>("text");
    scale({100, 12});
    setup_ignored_keys(ignored_keys);
    reload();
}


bool WidgetText_entry::is_hover()
{
    auto mouse = Input::getMouse();
    if (mouse.x < transform.position.x || mouse.x > transform.position.x + transform.scale.x)
        return false;
    if (mouse.y < transform.position.y || mouse.y > transform.position.y + transform.scale.y)
        return false;
    return true;
}

bool WidgetText_entry::is_clicked()
{
    return is_hover() && Input::getKeys(keyboard::LeftClick) == keyboard::KeyStatus::PRESSED;
}

void WidgetText_entry::onCreateView()
{}

void WidgetText_entry::onUpdateView()
{
    if (is_clicked())
        isfocus = true;
    else if (!is_hover() && Input::getKeys(keyboard::LeftClick) == keyboard::KeyStatus::PRESSED)
        isfocus = false;
    if (isfocus) {
        auto key_queue = Input::getKeysQueue();
        for (auto i = 0; i < key_queue.size; ++i) {
            if (key_queue.data[i].pressed) {
                if (key_queue.data[i].key == keyboard::Key::BackSpace) {
                    if (!data.empty())
                        data.pop_back();
                    continue;
                }
                if (key_queue.data[i].key == keyboard::Key::Enter) {
                    handler(data);
                    clear();
                    continue;
                }
                if (std::find(ignored_keys.begin(), ignored_keys.end(), key_queue.data[i].key) != ignored_keys.end())
                    continue;
                if (key_queue.data[i].pressed) {
                    data.push_back(key_queue.data[i].key + 'A' - 2);
                }
            }
        }
        if (key_queue.size)
            reload();
    }
    if (data.empty() && !is_placeholdermode) {
        is_placeholdermode = true;
        reload();
    }
    if (!data.empty() && is_placeholdermode) {
        is_placeholdermode = false;
        reload();
    }
}

void WidgetText_entry::onFinishView()
{}

void WidgetText_entry::reload()
{
    if (is_placeholdermode) {
        text->set_text(placeholder);
        text->set_color(placeholder_color);
    } else {
        text->set_color(textcolor);
        text->set_text(data);
    }
}

void WidgetText_entry::clear()
{
    data.clear();
    reload();
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
    textcolor = color;
    text->set_color(textcolor);
}

void WidgetText_entry::set_background(sf::Color color)
{
    background_color = color;
}

void WidgetText_entry::set_handler(std::function<void(std::string_view)> functor)
{
    handler = functor;
}

void WidgetText_entry::set_placeholder(const std::string &str)
{
    placeholder = str;
    reload();
}

void WidgetText_entry::set_placeholder_color(sf::Color color)
{
    placeholder_color = color;
    reload();
}




