/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _APP_VIEWS_FRAGMENTS_GAME_HPP_
#define _APP_VIEWS_FRAGMENTS_GAME_HPP_

#include "sdk/interfaces/Ifragment.hpp"
#include "app/views/home/widgets/console.hpp"

class Game : public Ifragment {
    bool is_connect = false;
    Console *console = nullptr;
    void onCreateView() final;
    void onUpdateView() final;
    void onFinishView() final;
public:
    Game(std::optional<std::string> &intent_ref, bidimensional::Transform &parent_trans, sf::RenderWindow &window);
    [[nodiscard]] bool *get_is_connect();
    void disconnect();
    void connect(const std::string &address);
    void set_console(Console *newconsole);
};

#endif