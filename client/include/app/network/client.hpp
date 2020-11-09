/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _APP_NETWORK_CLIENT_HPP_
#define _APP_NETWORK_CLIENT_HPP_

#include <functional>
#include <vector>
#include <utility>
#include <SFML/System/Clock.hpp>
#include "sdk/managers/inputs.hpp"
#include "app/views/home/widgets/console.hpp"
#include "app/network/protocol.hpp"
#include "app/network/udpsockmngr.hpp"
#include "app/network/tcpsockmngr.hpp"
#include "app/network/asset.hpp"

namespace network {
    class Client {
        enum class Status {
            NotConnected,
            AskForAssets,
            WaitingForAssets,
            DownloadAssets,
            Ready,
            Play
        } status = Status::NotConnected;
        std::string server_ip;
        short server_udp_port;
        short server_tcp_port;
        std::vector<std::pair<long, bool>> assets_ids_list;
        std::vector<Asset> assets;
        network::UdpSockMngr udp;
        network::TcpSockMngr tcp;
        sf::Clock timeout_clock;
        static constexpr auto timeout = 30000;
//        Input input;
        std::function<void(void)> onDisconnect_hdl = nullptr;
//        std::function<void(protocol::Message<protocol::udp::Code>)> receive_handler;
        Console *console = nullptr;
    public:
        void update();
        void setConsole(Console *new_console);
        void set_onDisconnect(std::function<void(void)> functor);
        void connect(const std::string &new_udp_server_address);
        void disconnect();
        void reset();
    };
}

#endif

// TODO examples

//class server {
//public:
//    server(boost::asio::io_context& io_context, short port)
//            : socket_(io_context, udp::endpoint(udp::v4(), port))
//    {
//        do_receive();
//    }
//
//    void do_receive()
//    {
//        socket_.async_receive_from(
//                boost::asio::buffer(data_, max_length), sender_endpoint_,
//                [this](boost::system::error_code ec, std::size_t bytes_recvd)
//                {
//                    if (!ec && bytes_recvd > 0)
//                    {
//                        do_send(bytes_recvd);
//                    }
//                    else
//                    {
//                        do_receive();
//                    }
//                });
//    }
//
//    void do_send(std::size_t length)
//    {
//        socket_.async_send_to(
//                boost::asio::buffer(data_, length), sender_endpoint_,
//                [this](boost::system::error_code /*ec*/, std::size_t /*bytes_sent*/)
//                {
//                    do_receive();
//                });
//    }
//
//private:
//    udp::socket socket_;
//    udp::endpoint sender_endpoint_;
//    enum { max_length = 1024 };
//    char data_[max_length];
//};