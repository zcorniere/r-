/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include "app/network/udpsockmngr.hpp"

network::UdpSockMngr::UdpSockMngr(Console &console, const std::string &ip, short port) :
    console(console), socket(context, udp::endpoint(udp::v4(), 0)) , resolver(context)
{
    udp::resolver::query query(udp::v4(), ip, std::to_string(port));
    endpoint = *resolver.resolve(query).begin();
    do_receive();
    run_thread = std::thread([this](){context.run();});
}

network::UdpSockMngr::~UdpSockMngr()
{
    context.stop();
    if (run_thread.joinable())
        run_thread.join();
}

void network::UdpSockMngr::do_receive()
{
    socket.async_wait(udp::socket::wait_read, [&](const boost::system::error_code &error) {
        auto len = socket.available();
        if (error || len < sizeof(protocol::MessageHeader<UdpCode>))
            return;
        std::vector<std::byte> buffer;
        buffer.resize(len);
        auto size = socket.receive(boost::asio::buffer(buffer, len));
        buffer.resize(size);

        protocol::MessageReceived<UdpCode> current(std::move(buffer));
        if (current.head().firstbyte != protocol::magic_number.first || current.head().secondbyte != protocol::magic_number.second) {
        } else if (!protocol::check_size(current.head().code, current.head().body_size)) {
            console.log("Error : UDP package has wrong body size");
        } else {
            received_messages.push_back(current);
        }
        do_receive();
    });
}

void network::UdpSockMngr::send(protocol::MessageToSend<UdpCode> message)
{
    std::size_t length = sizeof(message.head) + message.head.body_size;
    std::vector<std::byte> buffer;
    buffer.resize(length);
    std::memcpy(buffer.data(), &message.head, sizeof(message.head));
    std::memcpy(buffer.data() + sizeof(message.head), message.body.data(), message.head.body_size);

    if (message.head.code == protocol::udp::Code::Input) {
        auto keys_size = static_cast<std::uint32_t>(sizeof(protocol::input::KeysEvent) * protocol::input::keys_array_size);
        std::cout << std::dec << std::endl;
        std::cout << "I send Input: buffer.size(): " << std::dec << buffer.size() << " | length: " << length << std::endl;
        std::cout << "total sizeof : " << sizeof(protocol::udp::from_client::Input::nb_keys) + keys_size + sizeof(protocol::udp::from_client::Input::pos) << std::endl;
        std::cout << "message.head.firstbyte  : " <<  static_cast<int>(message.head.firstbyte) << std::endl;
        std::cout << "message.head.secondbyte : " << static_cast<int>(message.head.secondbyte) << std::endl;
        std::cout << "message.head.code       : " << std::hex << static_cast<int>(message.head.code) << std::endl;
        std::cout << "message.head.body_size  : " << std::dec << static_cast<int>(message.head.body_size) << std::endl;
        std::cout << "body:" << std::hex;
        for (auto i = 0; i < message.head.body_size; ++i) {
            std::cout << int(message.body[i]) << " ";
        }
        std::cout << std::dec << std::endl;
        std::cout << "cast in protocol::Input:";
    }


    socket.send_to(boost::asio::buffer(buffer, length), endpoint);
}

std::vector<protocol::MessageReceived<UdpCode>> network::UdpSockMngr::receive()
{
    auto ret = received_messages;
    received_messages.clear();
//    if (!received_messages.empty())
//        return std::vector<protocol::MessageReceived<UdpCode>>();
    return std::move(ret);
}




