/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include "app/network/tcpsockmngr.hpp"

network::TcpSockMngr::TcpSockMngr() :
    socket(io_context), resolver(io_context)
{
    reset();
}

void network::TcpSockMngr::setConsole(Console *new_console)
{
    console = new_console;
}

void network::TcpSockMngr::setHost(const std::string &ip, short port)
{
    // TODO
}

void network::TcpSockMngr::reset()
{
    is_connected = false;
    io_context.reset();
    socket.close();
    assets_ids_list.clear();
    assets.clear();
}

bool network::TcpSockMngr::isConnected() const
{
    return is_connected;
}

void network::TcpSockMngr::set_assets_ids_list(std::vector<std::pair<long, bool>> new_assets_ids_list)
{
    assets_ids_list = new_assets_ids_list;
}

bool network::TcpSockMngr::isDownloadFinished() const
{
    // TODO
    return false;
}

std::vector<Asset> network::TcpSockMngr::getAssets() const
{
    return assets;
}

