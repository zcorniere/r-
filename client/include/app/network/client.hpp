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
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "sdk/managers/inputs.hpp"
#include "app/views/home/widgets/console.hpp"
#include "app/network/protocol.hpp"
#include "app/network/udpsockmngr.hpp"
#include "app/network/tcpsockmngr.hpp"
#include "app/network/asset.hpp"

namespace network {
    class Client {
        sf::RenderWindow &window;
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
        static constexpr auto timeout = 10000;
        std::function<void(void)> onDisconnect_hdl = nullptr;
        Console *console = nullptr;
    public:
        explicit Client(sf::RenderWindow &p_window);
        void update();
        void setConsole(Console *new_console);
        void set_onDisconnect(std::function<void(void)> functor);
        void connect(const std::string &new_udp_server_address);
        void disconnect();
        void reset();
    };
}

#endif
