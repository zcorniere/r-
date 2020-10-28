/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include "components/window.hpp"
#include "components/interfaces/Ifragment.hpp"

void Ifragment::set_intent(const std::string &view)
{
    intent.emplace(view);
}

Ifragment *Ifragment::get_fragment(const std::string &key)
{
    auto item = std::find_if(fragments.begin(), fragments.end(), [&](const auto &pair){
        return pair.first == key;
    });
    if (item == fragments.end())
        return nullptr;
    return item->second;
}

Ifragment::Ifragment(std::optional<std::string> &view_intent, sf::RenderWindow &main_window) :
        intent(view_intent), window(main_window)
{}

Ifragment::~Ifragment()
{
    for (auto &fragment : fragments) {
        delete fragment.second;
    }
}

void Ifragment::runCreate()
{
    const auto parent_view = window.getView();
    compute_content();
    // background
    background.setFillColor(background_color);
    background.setSize(sf::Vector2f(width, height));
    background.setPosition(0, 0);
    // sort z_index
    std::sort(fragments.begin(), fragments.end(), [](const auto &left, const auto &right) {
        return left.second->z_index < right.second->z_index;
    });
    window.setView(content);
    for (auto &fragment : fragments) {
        fragment.second->runCreate();
    }
    onCreateView();
    window.setView(parent_view);
}

void Ifragment::runUpdate()
{
    window.setView(content);
    window.draw(background);
    onUpdateView();
    for (auto &fragment : fragments) {
        fragment.second->runUpdate();
    }
}

void Ifragment::runFinish()
{
    for (auto &fragment : fragments) {
        fragment.second->runFinish();
    }
    onFinishView();
}

void Ifragment::compute_content()   // TODO function to long, make it clean
{
    auto center = sf::Vector2<float>(width / 2, height / 2);
    const auto parent_view = window.getView();
    const auto parent_viewport = parent_view.getViewport();
    const auto parent_size = parent_view.getSize();
    // POSITION

//    const auto child_relative_x = 1 / (parent_size.x / x);
//    const auto child_relative_y = 1 / (parent_size.y / y);
//    auto posx_percent = parent_viewport.left;
//    auto posy_percent = parent_viewport.top;
//    if (child_relative_x < 0)
//        center.x += std::abs(x);
//    else
//        posx_percent += child_relative_x;
//    if (child_relative_y < 0)
//        center.y += std::abs(y);
//    else
//        posy_percent += child_relative_y;

    auto rel_x = x;
    auto rel_y = y;
    const auto abs_width = width;
    const auto abs_height = height;
    // final vars
    auto net_width = abs_width;
    auto net_height = abs_height;

    if (rel_x < 0) {
        const auto diff = std::abs(rel_x);
        rel_x = 0;
        net_width -= diff;
        center.x += diff;
    }
    if (rel_y < 0) {
        const auto diff = std::abs(rel_y);
        rel_y = 0;
        net_height -= diff;
        center.y += diff;
    }
    const auto abs_x = parent_viewport.left * window::WIDTH + rel_x;
    const auto abs_y = parent_viewport.top * window::HEIGHT + rel_y;
    // SIZE
    if (x + net_width > parent_size.x) {
        const auto diff = x + net_width - parent_size.x;
        net_width -= diff;
        center.x -= diff;
    }
    if (y + net_height > parent_size.y) {
        const auto diff = y + net_height - parent_size.y;
        net_height -= diff;
        center.y -= diff;
    }
    const auto abs_width_percent = net_width / window::WIDTH;
    const auto abs_height_percent = net_height / window::HEIGHT;
    const auto abs_posx_percent = abs_x / window::WIDTH;
    const auto abs_posy_percent = abs_y / window::HEIGHT;
    // BUILD VIEW
    content.setCenter(center);
    content.setSize(net_width, net_height);
    content.setViewport(sf::FloatRect(abs_posx_percent, abs_posy_percent, abs_width_percent, abs_height_percent));
}

void Ifragment::move(float x, float y, unsigned milliseconds)
{
    // TODO
}

