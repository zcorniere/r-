/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include "app/network/udpsockmngr.hpp"

network::UdpSockMngr::UdpSockMngr() :
    socket(io_context) , resolver(io_context)
{
    reset();
}

void network::UdpSockMngr::do_receive()
{
    socket.async_wait(udp::socket::wait_read, [&](const boost::system::error_code &error) {
        auto len = socket.available();
        if (error || len > sizeof(protocol::MessageHeader<UdpCode>))  // TODO check if is_running
            do_receive();
        std::vector<std::byte> buffer;
        buffer.resize(len);
        auto size = socket.receive(boost::asio::buffer(buffer, len));
        buffer.resize(size);
        protocol::MessageReceived<UdpCode> message(std::move(buffer));
        if (message.head().firstbyte != protocol::magic_number.first || message.head().secondbyte != protocol::magic_number.second)
            do_receive();
        received_messages.push_back(std::move(message));
    });
}

void network::UdpSockMngr::setConsole(Console *new_console)
{
    console = new_console;
}

void network::UdpSockMngr::setHost(const std::string &ip, short port)
{
//    boost::asio::connect(socket, resolver.resolve(ip, std::to_string(port)));
    is_connected = true;
    do_receive();   // start listening
}

void network::UdpSockMngr::reset()
{
    is_connected = false;
    io_context.reset();
    socket.close();
}

bool network::UdpSockMngr::isConnected() const
{
    return is_connected;
}

void network::UdpSockMngr::send(protocol::MessageToSend<UdpCode> message)
{
    // TODO
}

std::vector<protocol::MessageReceived<UdpCode>> network::UdpSockMngr::receive()
{
    // TODO & check magic number (if not valid return std::nullopt)
    std::vector<protocol::MessageReceived<UdpCode>> ret;
    return ret;
}



