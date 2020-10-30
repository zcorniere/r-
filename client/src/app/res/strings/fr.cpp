/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include "app/res/strings/common.hpp"
#include "app/res/strings/fr.hpp"

FrString::FrString()
{
    *this += CommonString();
    list.emplace("home", "ACCEUIL");
}
