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
        boost::asio::io_context &context;
        udp::socket socket;
        udp::resolver resolver;
        udp::endpoint endpoint;
        std::vector<protocol::MessageReceived<UdpCode>> received_messages;
        void do_receive();
        void do_send(protocol::MessageToSend<UdpCode> message);
    public:
        explicit UdpSockMngr(boost::asio::io_context &io_context);
        void setConsole(Console *new_console);
        void setHost(const std::string &ip, short port);
        void reset();
        [[nodiscard]] bool isConnected() const;
        void send(protocol::MessageToSend<UdpCode> message);
        std::vector<protocol::MessageReceived<UdpCode>> receive();
    };
}

#endif