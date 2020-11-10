/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <algorithm>
#include <cstring>
#include <utility>
#include "app/network/client.hpp"

network::Client::Client(sf::RenderWindow &p_window) :
    window(p_window)
{}

void network::Client::update()
{
    if (status == Status::NotConnected)
        return;
    if (status == Status::Play) {
        auto message_list = udp.receive();
        if (message_list.empty())
            return;
        for (auto &message : message_list) {
            // handle server disconnection
            if (message.head().code == UdpCode::Disconnect) {
                if (console) console->log("Server is disconnected");
                disconnect();
            }
            // handle server game instruction
            if (message.head().code == UdpCode::Sprite) {
                protocol::udp::from_server::Sprite sprite;
                std::memcpy(&sprite, message.body().data(), message.body().size());
                auto it = std::find_if(assets.begin(), assets.end(), [&](const auto &item){
                    if (item.type != Asset::Type::Texture)
                        return false;
                    if (item.id_asset != sprite.id_asset)
                        return false;
                    if (item.id_tile != sprite.id_sprite)
                        return false;
                    return true;
                });
                if (it != assets.end()) {
                    it->sprite.setRotation(sprite.rot.x);
                    it->sprite.setPosition(sprite.pos.x, sprite.pos.y);
                    it->sprite.scale(sprite.scale.x, sprite.scale.y);
                    window.draw(it->sprite);
                } else
                    console->log("Error [Play]: Sprite specified not found");
            }
            if (message.head().code == UdpCode::Sound) {
                protocol::udp::from_server::Sound sound;
                std::memcpy(&sound, message.body().data(), message.body().size());
                auto it = std::find_if(assets.begin(), assets.end(), [&](const auto &item){
                    if (item.type != Asset::Type::Sound)
                        return false;
                    if (item.id_asset != sound.id)
                        return false;
                    return true;
                });
                if (it != assets.end()) {
                    it->sound.setPitch(sound.pitch);
                    it->sound.setLoop(sound.isLooping);
                    it->sound.play();
                } else
                    console->log("Error [Play]: Sound specified not found");
            }
        }
        // send input
        protocol::MessageToSend<UdpCode> message;
        message.head.code = protocol::udp::Code::Input;
        message.head.body_size = sizeof(protocol::udp::from_client::Input);
        protocol::udp::from_client::Input body;
        auto mouse = Input::getMouse();
        auto keys = Input::getKeysQueue();
        body.pos = {static_cast<short>(mouse.x), static_cast<short>(mouse.y)};
        for (auto i = 0; i < keys.size; ++i) {
            body.keys[i].key = static_cast<protocol::input::Keys>(keys.data[i].key);
            body.keys[i].pressed = keys.data[i].pressed;
        }
        body.nb_keys = keys.size;
        std::memcpy(message.body.data(), &body, message.head.body_size);
        udp.send(message);
        return;
    }
    if (status == Status::AskForAssets) {
        if (!udp.isConnected())
            udp.setHost(server_ip, server_udp_port);
        if (udp.isConnected()) {
            protocol::MessageToSend<UdpCode> message;
            message.head.code = protocol::udp::Code::AskAssetList;
            message.head.body_size = sizeof(protocol::udp::from_client::AskAssetList);
            message.body.clear();
            udp.send(message);
            status = Status::WaitingForAssets;
            timeout_clock.restart();
            if (console) console->log("Success [AskForAssets]");
        }
    }
    if (status == Status::WaitingForAssets) {
        if (udp.isConnected()) {
            auto message_list = udp.receive();
            if (message_list.empty())
                return;
            for (auto &message : message_list) {
                if (message.head().code == UdpCode::AssetList) {
                    protocol::udp::from_server::AssetList assetlist;
                    auto body = message.body();
                    std::memcpy(&assetlist.port, body.data(), sizeof(assetlist.port));
                    body += sizeof(assetlist.port);
                    std::memcpy(&assetlist.size, body.data(), sizeof(assetlist.size));
                    body += sizeof(assetlist.size);
                    assetlist.list.resize(assetlist.size);
                    std::memcpy(assetlist.list.data(), body.data(), assetlist.size * sizeof(assetlist.list.front()));
                    server_tcp_port = static_cast<short>(assetlist.port);
                    for (auto i = 0; i < assetlist.size; ++i)
                        assets_ids_list.emplace_back(assetlist.list[i], false);
                    status = Status::DownloadAssets;
                    timeout_clock.restart();
                    if (console) console->log("Success [WaitingForAssets]");
                    break;
                } else {
                    if (console) console->log("Error [WaitingForAssets] : Server sent wrong data");
                    continue;
                }
            }
        }
    }
    if (status == Status::DownloadAssets) {
        if (!tcp.isConnected())
            tcp.setHost(server_ip, server_tcp_port);
        if (tcp.isConnected())
            tcp.set_assets_ids_list(assets_ids_list);
        if (tcp.isDownloadFinished()) {
            assets = tcp.getAssets();
            status = Status::Ready;
            timeout_clock.restart();
            if (console) console->log("Success [DownloadAssets]");
        }
    }
    if (status == Status::Ready) {
        protocol::MessageToSend<UdpCode> message;
        message.head.code = protocol::udp::Code::Ready;
        message.head.body_size = sizeof(protocol::udp::from_client::Ready);
        udp.send(message);
        status = Status::Play;
        timeout_clock.restart();
        if (console) console->log("Success [Ready]");
    }
    if (timeout_clock.getElapsedTime().asMilliseconds() >= timeout) {
        if (console) console->log("Error : Timed out");
        disconnect();
    }
}

void network::Client::setConsole(Console *new_console)
{
    console = new_console;
    udp.setConsole(console);
    tcp.setConsole(console);
}

void network::Client::set_onDisconnect(std::function<void(void)> functor)
{
    onDisconnect_hdl = std::move(functor);
}

static std::optional<std::pair<std::string, short>> parseAddress(const std::string &address)
{
    std::pair<std::string, short> ret;
    auto index = address.find_last_of(':');
    if (index == std::string::npos)
        return std::nullopt;
    ret.first = address.substr(0, index);
    ret.second = std::stoi(address.data() + index);
    return std::optional(ret);
}

void network::Client::connect(const std::string &new_udp_server_address)
{
    auto host = parseAddress(new_udp_server_address);
    if (host == std::nullopt) {
        if (console) console->log( "failed to parse address");
        disconnect();
        return;
    }
    server_ip = host.value().first;
    server_udp_port = host.value().second;
    if (console) console->log( "try to connect to : " + server_ip + ":" + std::to_string(server_udp_port));
    status = Status::AskForAssets;
    timeout_clock.restart();
}

void network::Client::disconnect()
{
    protocol::MessageToSend<UdpCode> message;
    message.head.code = protocol::udp::Code::Disconnect;
    message.head.body_size = sizeof(protocol::udp::Disconnect);
    udp.send(message);
    timeout_clock.restart();
    status = Status::NotConnected;
    onDisconnect_hdl();
    if (console) console->log("you have been disconnected");
    reset();
}

void network::Client::reset()
{
    server_ip.clear();
    server_udp_port = 0;
    server_tcp_port = 0;
    assets_ids_list.clear();
    tcp.reset();
    udp.reset();
}

