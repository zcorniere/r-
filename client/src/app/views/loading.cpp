/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <iostream>
#include "app/views/loading.hpp"

void LoadingView::onCreateView()
{
    std::cout << "create loading" << std::endl;
    set_intent("home");
}

void LoadingView::onUpdateView()
{
    // nothing
}

void LoadingView::onFinishView()
{
    std::cout << "finish loading" << std::endl;
}