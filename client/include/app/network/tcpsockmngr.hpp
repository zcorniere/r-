/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _APP_NETWORK_TCPSOCKMNGR_HPP_
#define _APP_NETWORK_TCPSOCKMNGR_HPP_

#include <thread>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <SFML/System/Clock.hpp>
#include <filesystem>
#include <atomic>
#include "app/views/home/widgets/console.hpp"
#include "app/network/protocol.hpp"
#include "app/network/asset.hpp"

using boost::asio::ip::tcp;
using boost::property_tree::ptree;
using boost::property_tree::read_json;

namespace network {
    class TcpSockMngr {
        static constexpr auto download_frame_size = 500;
        std::atomic<bool> is_download_finish = false;
        std::atomic<bool> is_connection_failed = false;
        Console &console;
        std::string ip;
        short port;
        boost::asio::io_context context;
        tcp::socket socket;
        tcp::resolver resolver;
        tcp::endpoint endpoint;
        std::vector<std::pair<long, bool>> assets_ids_list;
        std::vector<Asset> assets;
        std::thread run_thread;
        sf::Clock &timeout_clock;
        std::mutex socket_mutex;

        long receiveAsset(uint32_t body_size);
        void do_receive();
        void send(protocol::MessageToSend<TcpCode> message);
//        void do_send(protocol::MessageToSend<TcpCode> message);
        void downloadAsset(long asset_id);
        void downloadAllAssets();

        long loadAssetFromBytes(const std::vector<std::byte> &bytes,
                                bool cache = true);

        // caching
        static constexpr auto asset_cache_directory = "client_cache";
        std::string cachedAssetName(uint64_t asset_id);
        std::filesystem::path cachedAssetPath(uint64_t asset_id);
        void cacheAsset(uint64_t asset_id,
                        const std::vector<std::byte> &buffer);
        bool tryLoadingCachedAsset(uint64_t asset_id);
        void loadAllCachedAssets();

      public:
        TcpSockMngr(sf::Clock &timeout, Console &console, const std::string &ip, short port, std::vector<std::pair<long, bool>>);
        ~TcpSockMngr();
        [[nodiscard]] bool isDownloadFinished() const;
        [[nodiscard]] bool isConnectionFailed() const;
        [[nodiscard]] std::vector<Asset> getAssets();
    };
}

#endif
