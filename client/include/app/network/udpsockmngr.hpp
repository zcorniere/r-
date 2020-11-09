/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _APP_NETWORK_UDPSOCKMNGR_HPP_
#define _APP_NETWORK_UDPSOCKMNGR_HPP_

#include <vector>
#include <boost/asio.hpp>
#include "app/network/protocol.hpp"
#include "app/views/home/widgets/console.hpp"

using boost::asio::ip::udp;

namespace network {
    class UdpSockMngr {
        bool is_connected = false;
        Console *console = nullptr;
        boost::asio::io_context io_context;
        udp::socket socket;
        udp::resolver resolver;
    public:
        UdpSockMngr();
        void setConsole(Console *new_console);
        void setHost(const std::string &ip, short port);
        void reset();
        [[nodiscard]] bool isConnected() const;
        void send(protocol::Message<UdpCode> message);
        std::vector<protocol::Message<UdpCode>> receive();
    };
}

#endif