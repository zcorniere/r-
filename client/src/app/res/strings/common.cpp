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
    auto path = std::filesystem::current_path().string();
    list.emplace("full_path", path);    // TODO get absolute path of the exec instead of the current directory
    list.emplace("foxy_head_trans_coffe", path + "/assets/icon/foxy_head_trans_coffe.png");
    list.emplace("helvetica_font", path + "/assets/fonts/helvetica/helvetica.ttf");
    list.emplace("foxy_red_eye", path + "/assets/icon/foxy_red_eye.png");
    list.emplace("Loader_Blue", path + "/assets/loader/blue.png");
    list.emplace("Loader_Green", path + "/assets/loader/green.png");
}