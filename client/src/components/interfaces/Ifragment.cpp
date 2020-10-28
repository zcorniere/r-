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
    const auto child_relative_x = 1 / (window::WIDTH / x);
    const auto child_relative_y = 1 / (window::HEIGHT / y);
    auto posx_percent = parent_viewport.left;
    auto posy_percent = parent_viewport.top;
    if (child_relative_x < 0)
        center.x += std::abs(x);
    else
        posx_percent += child_relative_x;
    if (child_relative_y < 0)
        center.y += std::abs(y);
    else
        posy_percent += child_relative_y;
    // SIZE
    auto final_width = width;
    auto final_height = height;
    if (x + width > parent_size.x) {
        const auto diff = x + width - parent_size.x;
        final_width -= diff;
        center.x -= diff;
    }
    if (y + height > parent_size.y) {
        const auto diff = y + height - parent_size.y;
        final_height -= diff;
        center.y -= diff;
    }
    auto width_percent = 1 / (window::WIDTH / final_width);
    auto height_percent = 1 / (window::HEIGHT / final_height);
    // BUILD VIEW
    content.setCenter(center);
    content.setSize(final_width, final_height);
    content.setViewport(sf::FloatRect(posx_percent, posy_percent, width_percent, height_percent));
}

void Ifragment::move(float x, float y, unsigned milliseconds)
{
    // TODO
}

