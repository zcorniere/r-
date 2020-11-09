/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include "app/network/udpsockmngr.hpp"

network::UdpSockMngr::UdpSockMngr() :
    socket(io_context) , resolver(io_context)
{
    reset();
}

void network::UdpSockMngr::setConsole(Console *new_console)
{
    console = new_console;
}

void network::UdpSockMngr::setHost(const std::string &ip, short port)
{
    // TODO
}

void network::UdpSockMngr::reset()
{
    is_connected = false;
    io_context.reset();
    socket.close();
}

bool network::UdpSockMngr::isConnected() const
{
    return is_connected;
}

void network::UdpSockMngr::send(protocol::Message<UdpCode> message)
{
    // TODO
}

std::vector<protocol::Message<UdpCode>> network::UdpSockMngr::receive()
{
    // TODO & check magic number (if not valid return std::nullopt)
    std::vector<protocol::Message<UdpCode>> ret;
    ret.clear();
    return ret;
}


