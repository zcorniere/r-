/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _APP_RES_THEME_DARK_HPP_
#define _APP_RES_THEME_DARK_HPP_

#include "sdk/interfaces/Itheme.hpp"
#include "app/res/colors.hpp"

class DarkTheme : public Itheme<Colors> {
public:
    DarkTheme() : Itheme("", "", "") {};        // TODO set colors
};

#endif