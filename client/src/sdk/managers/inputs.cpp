/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include "sdk/managers/inputs.hpp"
#include <cassert>

void Input::init(Event *ev)
{
    event = ev;
}

sf::Vector2<int> Input::getMouse()
{
    return event->mouse;
}

keyboard::KeyStatus Input::getKeys(keyboard::Key key)
{
    return event->keys_state.at(key);
}

Event::KeysEvent Input::getKeysQueue()
{
    Event::KeysEvent keys_event;
    unsigned counter = 0;
    for (auto &[key, state] : Input::event->keys_state) {
        keys_event.data[counter].key = key;
        keys_event.data[counter].pressed =
            state == keyboard::KeyStatus::PRESSED;
        counter++;
        assert(counter < keys_event.data.size());
    }
    keys_event.size = counter - 1;
    return keys_event;
}

std::string Input::get_text_entered()
{
    return event->text_entered;
}
