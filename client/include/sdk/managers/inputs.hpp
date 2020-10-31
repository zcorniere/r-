/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _SDK_MANAGERS_INPUTS_H_
#define _SDK_MANAGERS_INPUTS_H_

#include <memory>
#include "sdk/managers/event.hpp"
#include "sdk/structures/keyboard.hpp"

class Input {
    static inline Event *event;
public:
    /**
     * Must be use only one time at the create of the main window
     * @param ev the main event manager
     */
    void init(Event *ev);
    [[nodiscard]] static sf::Vector2<int> getMouse();
    [[nodiscard]] static keyboard::KeyStatus getKeys(keyboard::Key key);
    [[nodiscard]] Event::KeysEvent static getKeysQueue();
    // TODO make others methods
};

#endif