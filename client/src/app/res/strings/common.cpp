/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <string>
#include <filesystem>
#include "app/res/strings/common.hpp"



CommonString::CommonString()
{
    list.emplace("full_path", std::filesystem::current_path().string());    // TODO get absolute path of the exec instead of the current directory
}