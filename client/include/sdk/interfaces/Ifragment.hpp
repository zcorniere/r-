/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _SDK_INTERFACES_IFRAGMENT_HPP_
#define _SDK_INTERFACES_IFRAGMENT_HPP_

#include <optional>
#include <string>
#include <vector>
#include <utility>
#include <SFML/Graphics.hpp>
#include "sdk/structures/bidimensional.hpp"
#include "sdk/interfaces/Itheme.hpp"

class Ifragment {
    std::optional<std::string> &intent;
    bidimensional::Transform &parent_transform;

    std::vector<std::pair<std::string, Ifragment *>> fragments;
    sf::RectangleShape background;
    void compute_content();
protected:
    sf::RenderWindow &window;
    /**
     * Must be set in fragment Ctor
     */
    bidimensional::Transform transform;

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
     * @tparam T T => fragment is a sub part of the View
     * @param key name
     */
    template<typename T>
    void add_fragment(const std::string &key) {
        static_assert(std::is_base_of<Ifragment, T>::value, "T doesn't derive from Ifragment");
        auto fragment = new T(intent, transform, window);
        fragments.emplace_back(key, fragment);
    }
    /**
     * Must be use only in a fragment Ctor
     * @tparam T => fragment is a sub part of the View
     * @param key name
     * @param theme use reinterpret_cast<Itheme<Icolors *> *>(std::make_unique<Theme>().get())
     */
    template<typename T>
    void add_fragment(const std::string &key, Itheme<Icolors *> *theme) {
        static_assert(std::is_base_of<Ifragment, T>::value, "T doesn't derive from Ifragment");
        auto fragment = new T(intent, transform, window, theme);
        fragments.emplace_back(key, fragment);
    }
    /**
     * Get a fragment from the local list
     * @param key unique name of the fragment
     * @return founded fragment or nullptr
     */
    [[nodiscard]] Ifragment *get_fragment(const std::string &key);
    /**
     * Same as get_fragment() but return the specified type
     * @tparam T fragment type
     * @param key unique name of the fragment
     * @return founded fragment or nullptr
     */
    template<typename T>
    [[nodiscard]] T *get_fragment(const std::string &key) {
        Ifragment *ret = get_fragment(key);
        return reinterpret_cast<T *>(ret);
    }
public:
    /**
     * Must be set in the fragment ctor
     */
    unsigned z_index = 0;
    Ifragment(std::optional<std::string> &view_intent, bidimensional::Transform &parent_trans, sf::RenderWindow &main_window);
    virtual ~Ifragment();
    void runCreate();
    void runUpdate();
    void runFinish();
    /**
     * Move fragment to a new position
     * @param x
     * @param y
     */
    void move(sf::Vector2<float> pos);
    /**
     * Rotate the fragment
     * @param angle in degrees
     */
    void rotate(float angle);
};

#endif