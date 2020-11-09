/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include <cstring>
#include "app/network/client.hpp"

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
            if (message.head.code == UdpCode::Disconnect) {
                if (console) console->log("Server is disconnected");
                disconnect();
            }
            // handle server game instruction
            if (message.head.code == UdpCode::Sprite) {
                // TODO
            }
            if (message.head.code == UdpCode::Sound) {
                // TODO
            }
        }
        // send input
        protocol::Message<UdpCode> message;
        message.head.code = protocol::udp::Code::Input;
        message.head.body_size = sizeof(protocol::udp::from_client::Input);
        protocol::udp::from_client::Input body; // TODO
        auto mouse = Input::getMouse();
        auto keys = Input::getKeysQueue();
        body.pos = {static_cast<short>(mouse.x), static_cast<short>(mouse.y)};
        for (auto i = 0; i < keys.size; ++i) {
            body.keys[i].key = static_cast<protocol::input::Keys>(keys.data[i].key);
            body.keys[i].pressed = keys.data[i].pressed;
        }
        body.nb_keys = keys.size;
        std::memcpy(&message.body, &body, message.head.body_size);
        udp.send(message);
        return;
    }
    if (status == Status::AskForAssets) {
        if (!udp.isConnected())
            udp.setHost(server_ip, server_udp_port);
        if (udp.isConnected()) {
            protocol::Message<UdpCode> message;
            message.head.code = protocol::udp::Code::AskAssetList;
            message.head.body_size = sizeof(protocol::udp::from_client::AskAssetList);
//            auto ptr = reinterpret_cast<std::byte*>(&protocol::udp::from_client::AskAssetList());
//            auto buffer = std::vector<std::byte>(ptr, ptr + sizeof s);
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
            auto message = message_list.begin();
            if (message->head.code == UdpCode::AssetList) {
                protocol::udp::from_server::AssetList assetlist;
                std::memcpy(&assetlist, message->body.data(), message->head.body_size);
                server_tcp_port = assetlist.port;
                for (auto i = 0; i < assetlist.size; ++i)
                    assets_ids_list.emplace_back(assetlist.list[i], false);
                status = Status::DownloadAssets;
                timeout_clock.restart();
                if (console) console->log("Success [WaitingForAssets]");
            } else {
                if (console) console->log("Error [WaitingForAssets] : Server sent wrong data");
                return;
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
        protocol::Message<UdpCode> message;
        message.head.code = protocol::udp::Code::Ready;
        message.head.body_size = sizeof(protocol::udp::from_client::Ready);
        message.body.clear();
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
    onDisconnect_hdl = functor;
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
    protocol::Message<UdpCode> message;
    message.head.code = protocol::udp::Code::Disconnect;
    message.head.body_size = sizeof(protocol::udp::Disconnect);
    message.body.clear();
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

