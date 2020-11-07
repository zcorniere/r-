/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include "app/res/theme.hpp"
#include "app/views/home/fragments/topbar.hpp"
#include "app/views/home/fragments/bottombar.hpp"
#include "app/views/home/fragments/game.hpp"
#include "app/window.hpp"

Game::Game(std::optional<std::string> &intent_ref, bidimensional::Transform &parent_trans, sf::RenderWindow &window) :
        Ifragment(intent_ref, parent_trans, window)
{
    transform.position = {0, TopBar::bar_height};
    transform.scale = {window::WIDTH, window::HEIGHT - TopBar::bar_height - BottomBar::bar_height};
    background_color = Theme().getColor("Transparent").value(); ;
    z_index = 1;
}

void Game::onCreateView()
{}

void Game::onUpdateView()
{}

void Game::onFinishView()
{}

bool *Game::get_is_connect()
{
    return &is_connect;
}

void Game::disconnect()
{
    is_connect = false;
    console->log("you have been disconnected");
    // TODO
}

void Game::connect(const std::string &address)
{
    if (is_connect)
        disconnect();
    is_connect = true;
    console->log( "try to connect to : " + address);
    // TODO
}

void Game::set_console(Console *newconsole)
{
    console = newconsole;
}
