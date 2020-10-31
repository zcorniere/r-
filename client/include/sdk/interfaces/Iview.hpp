/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _SDK_INTERFACES_IVIEW_HPP_
#define _SDK_INTERFACES_IVIEW_HPP_

#include <optional>
#include <type_traits>
#include <vector>
#include <utility>
#include <string>
#include <SFML/Graphics.hpp>
#include "sdk/interfaces/Ifragment.hpp"
#include "sdk/interfaces/Itheme.hpp"

class Iview {
    std::optional<std::string> intent = std::nullopt;
    std::vector<std::pair<std::string, Ifragment *>> fragments;
    bidimensional::Transform transform;
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
     * @tparam T fragment is a sub part of the View
     * @param key unique name of the fragment
     */
    template<typename T>
    void add_fragment(const std::string &key) {
        static_assert(std::is_base_of<Ifragment, T>::value, "T doesn't derive from Ifragment");
        auto fragment = new T(intent, transform, window);
        fragments.emplace_back(key, fragment);
    }
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
public:
    explicit Iview(sf::RenderWindow &main_window);
    virtual ~Iview();
    void runCreate();
    void runUpdate();
    void runFinish();
    [[nodiscard]] std::optional<std::string> get_intent();
};

#endif