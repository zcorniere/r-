/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include "app/network/protocol.hpp"

bool protocol::check_size(UdpCode type, uint32_t size) {
    if (type == UdpCode::Sprite) return size == sizeof(protocol::udp::from_server::Sprite);
    if (type == UdpCode::Sound) return size == sizeof(protocol::udp::from_server::Sound);
    if (type == UdpCode::AssetList) return size == sizeof(protocol::udp::from_server::AssetList);
    if (type == UdpCode::AskAssetList) return size == sizeof(protocol::udp::from_client::AskAssetList);
    if (type == UdpCode::Ready) return size == sizeof(protocol::udp::from_client::Ready);
    if (type == UdpCode::Input) return size == sizeof(protocol::udp::from_client::Input);
    if (type == UdpCode::Disconnect) return size == sizeof(protocol::udp::Disconnect);
    return false;
}

bool protocol::check_size(TcpCode type, uint32_t size) {
    if (type == TcpCode::AssetAsk) return size == sizeof(protocol::tcp::AssetAsk);
    if (type == TcpCode::AssetPackage) return size == sizeof(protocol::tcp::AssetPackage);
    return false;
}