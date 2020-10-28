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

Ifragment::Ifragment(std::optional<std::string> &view_intent, bidimensional::Transform &parent_trans, sf::RenderWindow &main_window) :
        intent(view_intent), parent_transform(parent_trans), window(main_window)
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
    background.setSize(transform.scale);
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
    auto center = sf::Vector2<float>(transform.scale.x / 2, transform.scale.y / 2);
    if (transform.position.x < 0) {
        transform.position.x = 0;
    }
    if (transform.position.y < 0) {
        transform.position.y = 0;
    }
    if (transform.position.x + transform.scale.x > parent_transform.scale.x) {
        transform.position.x = parent_transform.scale.x - transform.scale.x;
    }
    if (transform.position.y + transform.scale.y > parent_transform.scale.y) {
        transform.position.y = parent_transform.scale.y - transform.scale.y;
    }
    const auto abs_x = parent_transform.position.x + transform.position.x;
    const auto abs_y = parent_transform.position.y + transform.position.y;
    const auto abs_width_percent = transform.scale.x / window::WIDTH;
    const auto abs_height_percent = transform.scale.y / window::HEIGHT;
    const auto abs_posx_percent = abs_x / window::WIDTH;
    const auto abs_posy_percent = abs_y / window::HEIGHT;
    // BUILD VIEW
    content.setCenter(center);
    content.setSize(transform.scale.x, transform.scale.y);
    content.setViewport(sf::FloatRect(abs_posx_percent, abs_posy_percent, abs_width_percent, abs_height_percent));
}

void Ifragment::move(float x, float y, unsigned milliseconds)
{
    // TODO
}

