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
        if (!is_connected)
            return;
        auto len = socket.available();
        if (error || len < sizeof(protocol::MessageHeader<UdpCode>))
            do_receive();
        // TODO case protocol::from_server::AssetList dont work
        std::vector<std::byte> buffer;
        buffer.resize(len);
        auto size = socket.receive(boost::asio::buffer(buffer, len));
        buffer.resize(size);
        protocol::MessageReceived<UdpCode> message(std::move(buffer));
        if (message.head().firstbyte != protocol::magic_number.first || message.head().secondbyte != protocol::magic_number.second)
            do_receive();
        if (!protocol::check_size(message.head().code, message.head().body_size)) {
            console->log("Error : UDP package has wrong body size");
            do_receive();
        }
        received_messages.push_back(std::move(message));
    });
}

void network::UdpSockMngr::do_send(protocol::MessageToSend<UdpCode> message)
{
    std::size_t length = sizeof(message.head) + message.head.body_size;
    std::vector<std::byte> buffer;
    buffer.resize(length);
    std::memcpy(buffer.data(), &message.head, sizeof(message.head));
    std::memcpy(buffer.data() + sizeof(message.head), message.body.data(), message.head.body_size);
    socket.async_send_to(boost::asio::buffer(buffer, length), endpoint, [&](boost::system::error_code error, std::size_t nbytes) {
        if (error || nbytes != length)
            console->log("Error [UDP]: send error");
    });
}

void network::UdpSockMngr::setConsole(Console *new_console)
{
    console = new_console;
}

void network::UdpSockMngr::setHost(const std::string &ip, short port)
{
    is_connected = true;
    endpoint = resolver.resolve(ip, std::to_string(port))->endpoint();
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
    if (is_connected) {
        do_send(std::move(message));
    } else
        if (console) console->log("Error [UDP] : Before sending data, you must setHost");
}

std::vector<protocol::MessageReceived<UdpCode>> network::UdpSockMngr::receive()
{
    return std::move(received_messages);
}



