/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <string>
#include <boost/dll/runtime_symbol_info.hpp>
#include <filesystem>
#include <iostream>
#include "app/res/strings/common.hpp"

static std::filesystem::path getFullPath()
{
    boost::system::error_code ec;
    auto path = boost::dll::program_location(ec);
    if (ec != boost::system::errc::errc_t::success) {
        return std::filesystem::current_path().string();
    }
    return path.parent_path().string();
}

static std::filesystem::path getAssetsPath()
{
    auto bin_path = getFullPath();
    auto asset_path = bin_path;
    while (true) {
        if (std::filesystem::exists(asset_path / "client" / "assets"))
            return asset_path / "client" / "assets";
        if (std::filesystem::exists(asset_path / "share" / "r-type_client" / "assets"))
            return asset_path / "share" / "r-type_client" / "assets";
        if (asset_path == asset_path.parent_path())
            throw std::runtime_error("Coul not find asset directory");
        asset_path = asset_path.parent_path();
    }
}

CommonString::CommonString()
{
    auto path = getFullPath().string();
    auto asset_path = getAssetsPath().string();
    std::clog << "Found asset path: " << asset_path << std::endl;
    list.emplace("full_path", path);    // TODO get absolute path of the exec instead of the current directory
    list.emplace("helvetica_font", asset_path + "/fonts/helvetica/helvetica.ttf");
    list.emplace("foxy_red_eye", asset_path + "/icon/foxy_red_eye_white.png");
    list.emplace("foxy_head_trans_coffe", asset_path + "/icon/foxy_head_trans_redeye_coffe.png");
    list.emplace("foxy_head_trans_gray", asset_path + "/icon/foxy_head_trans_gray3.png");
    list.emplace("Loader_Blue", asset_path + "/loader/blue.png");
    list.emplace("Loader_Green", asset_path + "/loader/green.png");
    list.emplace("extend image", asset_path + "/extend.png");
}
