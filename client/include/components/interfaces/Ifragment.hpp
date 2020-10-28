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
    sf::RectangleShape background;
protected:
    sf::RenderWindow &window;
    /**
     * Must be set in the fragment ctor
     */
    float width = 100;
    /**
     * Must be set in the fragment ctor
     */
    float height = 100;
    /**
     * Must be set in the fragment ctor
     */
    float x = 0;
    /**
     * Must be set in the fragment ctor
     */
    float y = 0;
    /**
     * Must be set in the fragment ctor
     */
    sf::Color background_color = sf::Color::White;
    sf::View content;
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
    /**
     * Must be set in the fragment ctor
     */
    unsigned z_index = 0;
    Ifragment(std::optional<std::string> &view_intent, sf::RenderWindow &main_window);
    virtual ~Ifragment();
    void runCreate();
    void runUpdate();
    void runFinish();
};

#endif // _IFRAGMENT_HPP_