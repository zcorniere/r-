/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <algorithm>
#include "app/network/tcpsockmngr.hpp"

network::TcpSockMngr::TcpSockMngr(sf::Clock &timeout, Console &console, const std::string &ip, short port, std::vector<std::pair<long, bool>> assetlist) :
    timeout_clock(timeout), console(console), ip(ip), port(port), socket(context), resolver(context), assets_ids_list(std::move(assetlist))
{
    try {
        boost::asio::connect(socket, resolver.resolve(ip, std::to_string(port)));
    } catch (std::exception) {
        is_connection_failed = true;
        return;
    }
    do_receive();
    run_thread = std::thread([this](){context.run();});
    downloadAllAssets();
}

network::TcpSockMngr::~TcpSockMngr()
{
    context.stop();
    if (run_thread.joinable())
        run_thread.join();
}

long network::TcpSockMngr::receiveAsset(uint32_t body_size)
{
    auto bytes_to_read = body_size;
    std::vector<std::byte> buffer;
    std::array<std::byte, download_frame_size> sub_buffer;

    while (bytes_to_read) {
        if (socket.available()) {
            auto received_size = socket.receive(boost::asio::buffer(sub_buffer, sub_buffer.size()));
            if (received_size) {
                auto old_size = buffer.size();
                buffer.resize(old_size + received_size);
                std::memcpy(buffer.data() + old_size, sub_buffer.data(), received_size);
            }
            bytes_to_read -= received_size;
        }
    }
    boost::asio::const_buffer buff(buffer.data(), buffer.size());
    protocol::tcp::AssetPackage body;
    // type
    std::memcpy(&body.type, buff.data(), sizeof(body.type));
    buff += sizeof(body.type);
    // id_asset
    std::memcpy(&body.id_asset, buff.data(), sizeof(body.id_asset));
    buff += sizeof(body.id_asset);
    // size_data
    std::memcpy(&body.size_data, buff.data(), sizeof(body.size_data));
    buff += sizeof(body.size_data);
    // size_config
    std::memcpy(&body.size_config, buff.data(), sizeof(body.size_config));
    buff += sizeof(body.size_config);
    // data
    body.data.resize(body.size_data);
    std::memcpy(body.data.data(), buff.data(), body.size_data);
    buff += body.size_data;
    if (body.type == protocol::tcp::AssetPackage::Type::Texture) {
        // config
        body.config.resize(body.size_config);
        std::memcpy(body.config.data(), buff.data(), body.size_config);
        buff += body.size_config;
    }

    // body is build
    if (body.type == protocol::tcp::AssetPackage::Type::Sound) {  // Sound
        Asset asset;
        asset.type = Asset::Type::Sound;
        asset.id_asset = static_cast<long>(body.id_asset);
        asset.sound_buffer.loadFromMemory(body.data.data(), body.data.size());
        assets.push_back(asset);
    } else {    // Texture
        std::string config_str;
        config_str.resize(body.size_config);
        std::memcpy(config_str.data(), body.config.data(), body.size_config);
        std::istringstream is(config_str);
        ptree json;
        read_json(is, json);
        auto sprites = json.find("sprites");
        for (auto& v : sprites->second) {
            Asset asset;
            asset.config.id = v.second.get<int>("id");
            asset.config.origin_x = v.second.get<int>("origin_x");
            asset.config.origin_y = v.second.get<int>("origin_y");
            asset.config.width = v.second.get<int>("width");
            asset.config.height = v.second.get<int>("height");
            asset.type = Asset::Type::Texture;
            asset.id_asset = static_cast<long>(body.id_asset);
            asset.texture.loadFromMemory(body.data.data(), body.data.size());
            asset.id_tile = static_cast<long>(asset.config.id);
            assets.push_back(asset);
        }
    }
    return static_cast<long>(body.id_asset);
}

void network::TcpSockMngr::do_receive()
{
    socket.async_wait(tcp::socket::wait_read, [&](const boost::system::error_code &error) {
        if (error || socket.available() < sizeof(protocol::MessageHeader<UdpCode>)) {
            return;
        }
        // Get the header
        protocol::MessageHeader<TcpCode> header;
        auto len = sizeof(header);
        std::vector<std::byte> buff;
        buff.resize(len);
        auto size = socket.receive(boost::asio::buffer(buff, len));
        buff.resize(size);
        std::memcpy(&header, buff.data(), size);
        // check the header
        if (header.firstbyte != protocol::magic_number.first || header.secondbyte != protocol::magic_number.second)
            return;
        if (header.code != TcpCode::AssetPackage) {
            console.log("Error [TCP]: Server sent wrong data");
            return;
        }
        if (!header.body_size) {
            console.log("Error [TCP]: Server sent empty body");
            return;
        }
        // get the body & work on it
        auto asset_id = receiveAsset(header.body_size);
        // update my assets_ids_list
        auto it = std::find_if(assets_ids_list.begin(), assets_ids_list.end(), [&](auto &asset_id_item){
            return asset_id_item.first == asset_id;
        });
        if (it == assets_ids_list.end()) {
            console.log("Error [TCP]: Downloaded Asset is not present in assets_ids_list");
            return;
        }
        it->second = true;
        downloadAllAssets();
    });
}

void network::TcpSockMngr::send(protocol::MessageToSend<TcpCode> message)
{
    std::size_t length = sizeof(message.head) + message.head.body_size;
    std::vector<std::byte> buffer;
    buffer.resize(length);
    std::memcpy(buffer.data(), &message.head, sizeof(message.head));
    std::memcpy(buffer.data() + sizeof(message.head), message.body.data(), message.head.body_size);
    boost::asio::write(socket, boost::asio::buffer(buffer, length));
    do_receive();
}

void network::TcpSockMngr::downloadAsset(long asset_id) {
    protocol::MessageToSend<TcpCode> message;
    message.head.code = TcpCode::AssetAsk;
    protocol::tcp::AssetAsk asset_ask {static_cast<uint64_t>(asset_id)};
    message.head.body_size = sizeof(asset_ask);
    message.body.resize(message.head.body_size);
    std::memcpy(message.body.data(), &asset_ask, message.head.body_size);
    send(message);
}

void network::TcpSockMngr::downloadAllAssets()
{
    auto it = std::find_if(assets_ids_list.begin(), assets_ids_list.end(), [](const auto &asset_id){
        return !asset_id.second;
    });
    if (it == assets_ids_list.end()) {
        console.log("Success [TCP]: All downloads are completed");
        is_download_finish = true;
    } else {
        console.log("[TCP]: Downloading asset " + std::to_string(it->first));
        timeout_clock.restart();
        downloadAsset(it->first);
    }
}

bool network::TcpSockMngr::isDownloadFinished() const
{
    if (assets_ids_list.empty()) {
        console.log("Error [TCP]: Download: assets_ids_list is empty");
        return false;
    }
    return is_download_finish;
}

bool network::TcpSockMngr::isConnectionFailed() const
{
    return is_connection_failed;
}

std::vector<Asset> network::TcpSockMngr::getAssets() const
{
    if (!isDownloadFinished()) {
        throw ("Download is not finish");
    }
    return assets;
}



