/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _IVIEW_HPP_
#define _IVIEW_HPP_

#include <optional>
#include <SFML/Graphics.hpp>

class Iview {
    std::optional<std::string> intent = std::nullopt;
protected:
    sf::RenderWindow &window;
    /**
     * To change to another view
     * @param view is the target view
     */
    void set_intent(const std::string &view);
public:
    explicit Iview(sf::RenderWindow &main_window) : window(main_window) {};
    virtual void onCreateView() = 0;
    virtual void onUpdateView() = 0;
    virtual void onFinishView() = 0;
    [[nodiscard]] std::optional<std::string> get_intent();
};

#endif // _IVIEW_HPP_