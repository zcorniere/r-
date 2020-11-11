/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _APP_NETWORK_TCPSOCKMNGR_HPP_
#define _APP_NETWORK_TCPSOCKMNGR_HPP_

#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "app/views/home/widgets/console.hpp"
#include "app/network/protocol.hpp"
#include "app/network/asset.hpp"

using boost::asio::ip::tcp;
using boost::property_tree::ptree;
using boost::property_tree::read_json;

namespace network {
    class TcpSockMngr {
        bool is_connected = false;
        bool is_download_finish = false;
        Console *console = nullptr;
        boost::asio::io_context io_context;
        tcp::socket socket;
        tcp::resolver resolver;
        tcp::endpoint endpoint;
        std::vector<std::pair<long, bool>> assets_ids_list;
        std::vector<Asset> assets;
        long receiveAsset();
        void do_receive();
        void do_send(protocol::MessageToSend<TcpCode> message);
        void downloadAsset(long asset_id);
        void downloadAllAssets();
    public:
        TcpSockMngr();
        void setConsole(Console *new_console);
        void setHost(const std::string &ip, short port);
        void reset();
        [[nodiscard]] bool isConnected() const;
        void set_assets_ids_list(std::vector<std::pair<long, bool>> new_assets_ids_list);
        [[nodiscard]] bool isDownloadFinished() const;
        [[nodiscard]] std::vector<Asset> getAssets() const;
    };
}

struct SpriteConfig {
    int id;
    int origin_x;
    int origin_y;
    int width;
    int height;
};

#endif