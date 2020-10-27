/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _IVIEW_HPP_
#define _IVIEW_HPP_

#include <optional>
#include <type_traits>
#include <SFML/Graphics.hpp>
#include "components/interfaces/Ifragment.hpp"

class Iview {
    std::optional<std::string> intent = std::nullopt;
    std::vector<Ifragment *> fragments;
protected:
    sf::RenderWindow &window;
    virtual void onCreateView() = 0;
    virtual void onUpdateView() = 0;
    virtual void onFinishView() = 0;
    /**
     * To change to another view
     * @param view is the target view
     */
    void set_intent(const std::string &view);
    /**
     * Must be use only in a View Ctor
     * @tparam T => fragment is a sub part of the View
     */
    template<typename T>
    void add_fragment() {
        static_assert(std::is_base_of<Ifragment, T>::value, "T doesn't derive from Ifragment");
        auto fragment = new T(intent, window);
        fragments.push_back(fragment);
    }
public:
    explicit Iview(sf::RenderWindow &main_window) : window(main_window) {};
    void runCreate();
    void runUpdate();
    void runFinish();
    [[nodiscard]] std::optional<std::string> get_intent();
};

#endif // _IVIEW_HPP_