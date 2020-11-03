/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <iostream>
#include "app/views/fragments/topbar.hpp"
#include "app/views/fragments/bottombar.hpp"
#include "app/views/fragments/game.hpp"
#include "app/window.hpp"

Game::Game(std::optional<std::string> &intent_ref, bidimensional::Transform &parent_trans, sf::RenderWindow &window) :
        Ifragment(intent_ref, parent_trans, window)
{
    transform.position = {0, TopBar::BARHEIGHT};
    transform.scale = {window::WIDTH, window::HEIGHT - TopBar::BARHEIGHT - BottomBar::BARHEIGHT};
    background_color = sf::Color::Black;
}

void Game::onCreateView()
{
    std::cout << "Create Game" << std::endl;
}

void Game::onUpdateView()
{}

void Game::onFinishView()
{
    std::cout << "Finish Game" << std::endl;
}
