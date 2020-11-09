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
        Ifragment(intent_ref, parent_trans, window), client(window)
{
    transform.position = {0, TopBar::bar_height};
    transform.scale = {window::WIDTH, window::HEIGHT - TopBar::bar_height - BottomBar::bar_height};
    background_color = Theme().getColor("Transparent").value(); ;
    z_index = 1;
    client.set_onDisconnect([&](){
        is_connect = false;
    });
}

void Game::onCreateView()
{
    client.setConsole(console);
}

void Game::onUpdateView()
{
    try {
        client.update();
    } catch (std::exception e) {
        console->log(e.what());
        disconnect();
    }
}

void Game::onFinishView()
{}

bool *Game::get_is_connect()
{
    return &is_connect;
}

void Game::disconnect()
{
    client.disconnect();
}

void Game::connect(const std::string &address)
{
    if (is_connect)
        disconnect();
    is_connect = true;
    client.connect(address);
}

void Game::set_console(Console *newconsole)
{
    console = newconsole;
}
