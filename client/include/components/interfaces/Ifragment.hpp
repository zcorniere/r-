/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _IFRAGMENT_HPP_
#define _IFRAGMENT_HPP_

#include <optional>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class Ifragment {
    std::optional<std::string> &intent;
    std::vector<Ifragment *> fragments;
protected:
    sf::RenderWindow &window;
    float width = 100;
    float height = 100;
    float x = 0;
    float y = 0;
    unsigned z_index = 0;
    virtual void onCreateView() = 0;
    virtual void onUpdateView() = 0;
    virtual void onFinishView() = 0;
    /**
     * To change to another view
     * @param view is the target view
     */
    void set_intent(const std::string &view);
    /**
     * Must be use only in a fragment Ctor
     * @tparam T => fragment is a sub part of the View
     */
    template<typename T>
    void add_fragment() {
        static_assert(std::is_base_of<Ifragment, T>::value, "T doesn't derive from Ifragment");
        auto fragment = new T(intent, window);
        fragments.push_back(fragment);
    }
public:
    Ifragment(std::optional<std::string> &view_intent, sf::RenderWindow &main_window);
    void runCreate();
    void runUpdate();
    void runFinish();
};

#endif // _HOME_HPP_